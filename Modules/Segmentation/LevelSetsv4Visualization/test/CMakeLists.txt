itk_module_test()
set(ITKLevelSetsv4VisualizationTests
# visualization
vtkVisualize2DLevelSetImageBaseTest
vtkVisualize2DWhitakerLevelSetTest
#vtkVisualize2DShiLevelSetTest
#vtkVisualize2DMalcolmLevelSetTest
itkImageToRGBVTKImageFilterTest
vtkVisualize2DWhitakerLevelSetLayersTest
vtkVisualize2DShiLevelSetLayersTest
vtkVisualize2DMalcolmLevelSetLayersTest
)

CreateTestDriver(ITKLevelSetsv4Visualization  "${ITKLevelSetsv4Visualization-Test_LIBRARIES}" "${ITKLevelSetsv4VisualizationTests}")

itk_add_test(NAME vtkVisualize2DLevelSetImageBaseTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DLevelSetImageBaseTest)

itk_add_test(NAME vtkVisualize2DWhitakerLevelSetTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DWhitakerLevelSetTest)

#itk_add_test(NAME vtkVisualize2DShiLevelSetTest
#  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DShiLevelSetTest)

#itk_add_test(NAME vtkVisualize2DMalcolmLevelSetTest
#  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DMalcolmLevelSetTest)

itk_add_test(NAME itkImageToRGBVTKImageFilterTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver itkImageToRGBVTKImageFilterTest)

itk_add_test(NAME vtkVisualize2DWhitakerLevelSetLayersTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DWhitakerLevelSetLayersTest)

itk_add_test(NAME vtkVisualize2DShiLevelSetLayersTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DShiLevelSetLayersTest)

itk_add_test(NAME vtkVisualize2DMalcolmLevelSetLayersTest
  COMMAND ITKLevelSetsv4VisualizationTestDriver vtkVisualize2DMalcolmLevelSetLayersTest)
