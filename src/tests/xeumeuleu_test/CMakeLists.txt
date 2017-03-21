find_package(Boost COMPONENTS system filesystem unit_test_framework thread REQUIRED)
find_package(XercesC REQUIRED)
include_directories(${xeumeuleu_SOURCE_DIR}/src/libraries
                    ${Boost_INCLUDE_DIRS}
                    ${XercesC_INCLUDE_DIR})
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(xeumeuleu_test attribute_test.cpp
                              attributes_test.cpp
                              call_test.cpp
                              cdata_test.cpp
                              content_test.cpp
                              context_test.cpp
                              customization_test.cpp
                              encoding_test.cpp
                              list_test.cpp
                              namespace_test.cpp
                              optional_test.cpp
                              patterns_test.cpp
                              pretty_print_test.cpp
                              thread_test.cpp
                              trim_test.cpp
                              validation_test.cpp
                              value_test.cpp
                              xeumeuleu_test_pch.cpp
                              xeumeuleu_test_pch.h
                              xibufferstream_test.cpp
                              xifstream_test.cpp
                              ximultistream_test.cpp
                              xistreamstream_test.cpp
                              xistringstream_test.cpp
                              xisubstream_test.cpp
                              xobufferstream_test.cpp
                              xofstream_test.cpp
                              xostream_xistream_test.cpp
                              xostreamstream_test.cpp
                              xostringstream_test.cpp
                              xosubstream_test.cpp)
target_link_libraries(xeumeuleu_test
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${XercesC_LIBRARY})
add_test(NAME xeumeuleu_test COMMAND xeumeuleu_test --result_code=no --report_level=no --log_level=warning --data_directory=../../data/tests/xeumeuleu_test)