WRAP_LIBRARY(ITKMesh)

set(WRAPPER_LIBRARY_DEPENDS ITKTransform)

set(WRAPPER_LIBRARY_GROUPS
  itkMeshBase
  itkMeshSource
  itkImageToMeshFilter
  itkMeshToMeshFilter
)

set(WRAPPER_LIBRARY_LINK_LIBRARIES ${ITK_LIBRARIES})

AUTO_INCLUDE_MODULES()
END_WRAP_LIBRARY()
