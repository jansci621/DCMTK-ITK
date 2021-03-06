/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

// Insight classes
#include "itkImageRegionIterator.h"


#include "itkScalarImageToRunLengthMatrixFilter.h"

int itkScalarImageToRunLengthMatrixFilterTest(int, char* [] )
{

  //Data definitions
  const unsigned int  IMGWIDTH         =  5;
  const unsigned int  IMGHEIGHT        =  5;
  const unsigned int  NDIMENSION       =  2;


  //------------------------------------------------------
  //Create a simple test images
  //------------------------------------------------------
  typedef itk::Image<unsigned char, NDIMENSION> InputImageType;

  typedef itk::ImageRegionIterator< InputImageType > InputImageIterator;


  InputImageType::Pointer image = InputImageType::New();
  InputImageType::Pointer mask = InputImageType::New();


  InputImageType::SizeType inputImageSize = {{ IMGWIDTH, IMGHEIGHT }};

  InputImageType::RegionType region;

  region.SetSize( inputImageSize );
    {
    InputImageType::IndexType index;
    index.Fill(0);
    region.SetIndex( index );
    }

  //--------------------------------------------------------------------------
  // Set up the image first. It looks like:
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //--------------------------------------------------------------------------

  image->SetRegions( region );
  image->Allocate();

  // setup the iterator
  InputImageIterator imageIt( image, image->GetBufferedRegion() );

  imageIt.GoToBegin();

  for(unsigned int i = 0; i < 5; i++)
    {
    for(unsigned int j = 0; j < 5; j++, ++imageIt)
      {
      imageIt.Set(j % 2 + 1);
      }
    }

  //--------------------------------------------------------------------------
  // Set up the mask next. It looks like:
  //  0 0 0 0 0
  //  0 0 1 0 0
  //  0 0 1 0 0
  //  0 0 1 0 0
  //  0 0 0 0 0
  //--------------------------------------------------------------------------

  mask->SetRegions( region );
  mask->Allocate();

  // setup the iterator
  InputImageIterator maskIt( mask, mask->GetBufferedRegion() );
  maskIt.GoToBegin();
  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++, ++maskIt)
      {
      if (j == 2 && i > 0 && i < 4)
        {
        maskIt.Set(1);
        }
      else
        {
        maskIt.Set(0);
        }
      }

  try
    {

    typedef itk::Statistics::ScalarImageToRunLengthMatrixFilter<
      InputImageType> FilterType;

    FilterType::Pointer filter = FilterType::New();

    filter->SetInput(image);

    InputImageType::OffsetType offset1 = {{0, 1}};
    InputImageType::OffsetType offset2 = {{1, 0}};
    FilterType::OffsetVectorPointer offsetV =
    FilterType::OffsetVector::New();
    offsetV->push_back(offset1);
    offsetV->push_back(offset2);

    filter->SetOffsets( offsetV );
    filter->SetMaskImage( mask );
    filter->SetPixelValueMinMax( 0, 2 );
    filter->SetDistanceValueMinMax( 0, 8 );
    filter->SetNumberOfBinsPerAxis( 5 );
    filter->Update();
    const FilterType::HistogramType * hist = filter->GetOutput();


    //--------------------------------------------------------------------------
    // Test the histogram.
    //--------------------------------------------------------------------------
    bool passed = true;

    unsigned int frequencies[9] = {0, 0, 0, 0, 0, 0, 3, 0, 1};

    unsigned int count = 0;
    for( unsigned int i = 0; i < 3; i++ )
      {
      for( unsigned int j = 0; j < 3; j++ )
        {
        typedef FilterType::HistogramType::IndexType IndexType;
        IndexType index( hist->GetMeasurementVectorSize() );
        index[0] = i;
        index[1] = j;
        if( hist->GetFrequency( index ) != frequencies[count] )
          {
          std::cerr << "Expected frequency = " << frequencies[count]
            << ", calculated = "
            << hist->GetFrequency( index ) << std::endl;
          passed = false;
          }
        count++;
        }
      }
    unsigned int totalF = hist->GetTotalFrequency();
    if( totalF != 4 )
      {
      std::cerr << "Expected total frequency = 4, calculated = "
        << totalF << std::endl;
      passed = false;
      }

    filter = FilterType::New();

    filter->SetInput( image );
    filter->SetOffsets( offsetV );
    filter->SetMaskImage( mask );
    filter->SetInsidePixelValue( 0 );
    filter->SetPixelValueMinMax( 0, 2 );
    filter->SetDistanceValueMinMax( 0, 8 );
    filter->SetNumberOfBinsPerAxis( 5 );

    if ( filter->GetInsidePixelValue() != 0 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetInsidePixelValue() is not returning the expected value"
        << std::endl;
      passed = false;
      }
    if ( filter->GetMaskImage() == NULL )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "Mask should not be null." << std::endl;
      passed = false;
      }
    if( filter->GetMin() != 0 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetMin() is not returning the expected value"
        << std::endl;
      passed = false;
      }
    if( filter->GetMax() != 2 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetMax() is not returning the expected value"
        << std::endl;
      passed = false;
      }
    if( filter->GetMinDistance() != 0 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetMinDistance() is not returning the expected value"
        << std::endl;
      passed = false;
      }
    if( filter->GetMaxDistance() != 8 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetMaxDistance() is not returning the expected value"
        << std::endl;
      passed = false;
      }

    const FilterType::OffsetVector *offsetVector = filter->GetOffsets();
    if( offsetVector->size() != 2 ||
      (*offsetVector)[0][0] != 0 || (*offsetVector)[0][1] != 1 ||
      (*offsetVector)[1][0] != 1 || (*offsetVector)[1][1] != 0 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetOffsets() is not returning the correct offsets"
        << std::endl;
      passed = false;
      }
    if( filter->GetNumberOfBinsPerAxis() != 5 )
      {
      std::cerr << "Error: " << std::endl;
      std::cerr << "GetNumberOfBinsPerAxis() is not returning the expected value"
        << std::endl;
      passed = false;
      }

    filter->Update();
    hist = filter->GetOutput();

    unsigned int frequencies2[9] = {0, 12, 0, 0, 0, 0, 12, 0, 0};

    count = 0;
    for( unsigned int i = 0; i < 3; i++ )
      {
      for( unsigned int j = 0; j < 3; j++ )
        {
        typedef FilterType::HistogramType::IndexType IndexType;
        IndexType index( hist->GetMeasurementVectorSize() );
        index[0] = i;
        index[1] = j;
        if( hist->GetFrequency( index ) != frequencies2[count] )
          {
          std::cerr << "Expected frequency2 = " << frequencies2[count]
            << ", calculated = "
            << hist->GetFrequency( index ) << std::endl;
          passed = false;
          }
        count++;
        }
      }


    filter->Print( std::cout, 3 );

    if (!passed)
      {
      std::cerr << "Test failed" << std::endl;
      return EXIT_FAILURE;
      }
    else
      {
      std::cerr << "Test succeeded" << std::endl;
      return EXIT_SUCCESS;
      }

    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    std::cerr << "Test failed" << std::endl;
    return EXIT_FAILURE;
    }
}
