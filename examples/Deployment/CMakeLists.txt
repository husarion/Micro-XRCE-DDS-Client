# Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 2.8.12)
if (${CMAKE_VERSION} VERSION_GREATER 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()


if(NOT PROFILE_CREATE_ENTITIES_REF OR NOT PROFILE_CREATE_ENTITIES_XML OR NOT PROFILE_READ_ACCESS OR NOT PROFILE_UDP_TRANSPORT)
    message(WARNING "Can not compile example: The profiles PROFILE_CREATE_ENTITIES_REF, PROFILE_CREATE_ENTITIES_XML, PROFILE_READ_ACCESS and PROFILE_UDP_TRANSPORT must be enabled.")
else()

    project(ConfiguratorClient)
    add_executable(ConfiguratorClient configurator_client.c HelloWorld.c HelloWorldWriter.c)
    target_link_libraries(ConfiguratorClient micrortps_client)

    project(Publisher)
    add_executable(Publisher publisher.c HelloWorld.c HelloWorldWriter.c)
    target_link_libraries(Publisher micrortps_client)

    project(Subscriber)
    add_executable(Subscriber subscriber.c HelloWorld.c)
    target_link_libraries(Subscriber micrortps_client)

    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION examples/micrortps/client/${PROJECT_NAME}/${BIN_INSTALL_DIR}
        )

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/
        DESTINATION  examples/micrortps/client/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
                       PATTERN "*.c"
                       PATTERN "*.idl"
        )
endif()