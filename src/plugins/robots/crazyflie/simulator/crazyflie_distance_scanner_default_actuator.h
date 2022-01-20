/**
 * @file <argos3/plugins/robots/crazyflie/simulator/crazyflie_distance_scanner_default_actuator.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef CRAZYFLIE_DISTANCE_SCANNER_DEFAULT_ACTUATOR_H
#define CRAZYFLIE_DISTANCE_SCANNER_DEFAULT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CCrazyflieDistanceScannerDefaultActuator;
}

#include <argos3/plugins/robots/crazyflie/control_interface/ci_crazyflie_distance_scanner_actuator.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_distance_scanner_equipped_entity.h>
#include <argos3/core/simulator/actuator.h>

namespace argos {

   class CCrazyflieDistanceScannerDefaultActuator : public CSimulatedActuator,
                                                  public CCI_CrazyflieDistanceScannerActuator {

   public:

  	  static const Real RPM_TO_RADIANS_PER_SEC;

      CCrazyflieDistanceScannerDefaultActuator();
      virtual ~CCrazyflieDistanceScannerDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void SetAngle(const CRadians& c_angle);
      virtual void SetRPM(Real f_rpm);

      virtual void Enable();
      virtual void Disable();

      virtual void Update();
      virtual void Reset();

   private:

      CCrazyflieDistanceScannerEquippedEntity* m_pcDistanceScannerEquippedEntity;

      CRadians m_cDesiredRotation;
      Real     m_fDesiredRotationSpeed;
      UInt8    m_unDesiredMode;

   };

}

#endif
