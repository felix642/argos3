#
# Crazyflie headers
#
# argos3/plugins/robots/crazyflie/simulator
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_CONTROLINTERFACE
  control_interface/ci_crazyflie_distance_scanner_sensor.h
  control_interface/ci_crazyflie_distance_scanner_actuator.h)
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_SIMULATOR
    simulator/crazyflie_entity.h
    simulator/pointmass3d_crazyflie_model.h
    simulator/crazyflie_distance_scanner_default_actuator.h
    simulator/crazyflie_distance_scanner_equipped_entity.h
    simulator/crazyflie_distance_scanner_rotzonly_sensor.h
    )
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Crazyflie sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_CONTROLINTERFACE}
  control_interface/ci_crazyflie_distance_scanner_sensor.cpp
  control_interface/ci_crazyflie_distance_scanner_actuator.cpp)
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_SIMULATOR}
    simulator/crazyflie_entity.cpp
    simulator/pointmass3d_crazyflie_model.cpp
    simulator/crazyflie_distance_scanner_default_actuator.cpp
    simulator/crazyflie_distance_scanner_equipped_entity.cpp
    simulator/crazyflie_distance_scanner_rotzonly_sensor.cpp
    )
  # Compile the graphical visualization only if the necessary libraries have been found
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_SIMULATOR}
      simulator/qtopengl_crazyflie.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE}
      simulator/qtopengl_crazyflie.h
      simulator/qtopengl_crazyflie.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create Crazyflie plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_crazyflie SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_CRAZYFLIE})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_crazyflie
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_pointmass3d)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_crazyflie argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
endif(ARGOS_COMPILE_QTOPENGL)

install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/crazyflie/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_CRAZYFLIE_SIMULATOR}      DESTINATION include/argos3/plugins/robots/crazyflie/simulator)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_crazyflie
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
