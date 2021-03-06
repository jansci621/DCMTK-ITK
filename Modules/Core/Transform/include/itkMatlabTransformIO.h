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
#ifndef __itkMatlabTransformIO_h
#define __itkMatlabTransformIO_h
#include "itkTransformIOBase.h"

namespace itk
{
class ITK_EXPORT MatlabTransformIO:public TransformIOBase
{
public:
  typedef MatlabTransformIO             Self;
  typedef TransformIOBase               Superclass;
  typedef SmartPointer< Self >          Pointer;
  typedef TransformBase                 TransformType;
  typedef Superclass::TransformPointer  TransformPointer;
  typedef Superclass::TransformListType TransformListType;
  /** Run-time type information (and related methods). */
  itkTypeMacro(MatlabTransformIO, TransformIOBase);
  itkNewMacro(Self);

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanReadFile(const char *);

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanWriteFile(const char *);

  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read();

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegions has been set properly. The buffer is cast to a
   * pointer to the beginning of the image data. */
  virtual void Write();

protected:
  MatlabTransformIO();
  virtual ~MatlabTransformIO();
};
}
#endif // __itkMatlabTransformIO_h
