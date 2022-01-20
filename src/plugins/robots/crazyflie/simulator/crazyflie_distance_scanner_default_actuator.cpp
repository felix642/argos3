/**
 * @file <argos3/plugins/robots/crazyflie/simulator/crazyflie_distance_scanner_default_actuator.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "crazyflie_distance_scanner_default_actuator.h"

namespace argos {

	 const Real CCrazyflieDistanceScannerDefaultActuator::RPM_TO_RADIANS_PER_SEC = ARGOS_PI / 30.0f;

   /****************************************/
   /****************************************/

   CCrazyflieDistanceScannerDefaultActuator::CCrazyflieDistanceScannerDefaultActuator() :
      m_fDesiredRotationSpeed(0.0f),
      m_unDesiredMode(CCrazyflieDistanceScannerEquippedEntity::MODE_OFF) {}

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcDistanceScannerEquippedEntity = &(c_entity.GetComponent<CCrazyflieDistanceScannerEquippedEntity>("distance_scanner"));
      m_pcDistanceScannerEquippedEntity->Enable();
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::SetAngle(const CRadians& c_angle) {
      m_unDesiredMode = CCrazyflieDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
      m_cDesiredRotation = c_angle;
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::SetRPM(Real f_rpm) {
      m_unDesiredMode = CCrazyflieDistanceScannerEquippedEntity::MODE_SPEED_CONTROL;
      m_fDesiredRotationSpeed = f_rpm * RPM_TO_RADIANS_PER_SEC;
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::Enable() {
      m_unDesiredMode = CCrazyflieDistanceScannerEquippedEntity::MODE_POSITION_CONTROL;
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::Disable() {
      m_unDesiredMode = CCrazyflieDistanceScannerEquippedEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::Update() {
      m_pcDistanceScannerEquippedEntity->SetMode(m_unDesiredMode);
      if(m_unDesiredMode == CCrazyflieDistanceScannerEquippedEntity::MODE_POSITION_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotation(m_cDesiredRotation);
      }
      else if(m_unDesiredMode == CCrazyflieDistanceScannerEquippedEntity::MODE_SPEED_CONTROL) {
         m_pcDistanceScannerEquippedEntity->SetRotationSpeed(m_fDesiredRotationSpeed);
      }
   }

   /****************************************/
   /****************************************/

   void CCrazyflieDistanceScannerDefaultActuator::Reset() {
      m_cDesiredRotation = CRadians::ZERO;
      m_fDesiredRotationSpeed = 0.0f;
      m_unDesiredMode = CCrazyflieDistanceScannerEquippedEntity::MODE_OFF;
   }

   /****************************************/
   /****************************************/

   REGISTER_ACTUATOR(CCrazyflieDistanceScannerDefaultActuator,
                     "crazyflie_distance_scanner", "default",
                     "Carlo Pinciroli [ilpincy@gmail.com]",
                     "1.0",
                     "The crazyflie distance scanner actuator.",
                     "This actuator controls the crazyflie distance scanner. For a complete\n"
                     "description of its usage, refer to the ci_crazyflie_distance_scanner_actuator\n"
                     "file.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <crazyflie_distance_scanner implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "None for the time being.\n",
                     "Usable"
      );

}
