find_package(Boost COMPONENTS system filesystem unit_test_framework thread REQUIRED)
find_package(XercesC REQUIRED)
find_package(XalanC REQUIRED)
include_directories(${xeumeuleu_SOURCE_DIR}/src/libraries
                    ${Boost_INCLUDE_DIRS}
                    ${XercesC_INCLUDE_DIR}
                    ${XalanC_INCLUDE_DIR})
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(xeuseuleu_test parameter_test.cpp
                              xbuffertransform_test.cpp
                              xeuseuleu_test_pch.cpp
                              xeuseuleu_test_pch.h
                              xftransform_test.cpp
                              xstringtransform_test.cpp)
target_link_libraries(xeuseuleu_test
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${XercesC_LIBRARY}
                      ${XalanC_LIBRARY})
add_test(NAME xeuseuleu_test COMMAND xeuseuleu_test --result_code=no --report_level=no --log_level=warning --data_directory=../../data/tests/xeuseuleu_test)