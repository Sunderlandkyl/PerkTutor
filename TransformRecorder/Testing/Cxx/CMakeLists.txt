set(KIT qSlicer${MODULE_NAME}Module)

#-----------------------------------------------------------------------------
set(KIT_TEST_SRCS
  #qSlicer${MODULE_NAME}ModuleTest.cxx
  )
  
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

#-----------------------------------------------------------------------------
slicerMacroConfigureModuleCxxTestDriver(
  NAME ${KIT}
  SOURCES ${KIT_TEST_SRCS}
  WITH_VTK_DEBUG_LEAKS_CHECK
  WITH_VTK_ERROR_OUTPUT_CHECK
  )

#-----------------------------------------------------------------------------
#simple_test(qSlicer${MODULE_NAME}ModuleTest)