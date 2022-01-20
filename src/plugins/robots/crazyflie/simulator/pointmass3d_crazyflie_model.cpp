/**
 * @file <argos3/plugins/robots/foot-bot/simulator/pointmass3d_crazyflie_model.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "pointmass3d_crazyflie_model.h"
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/math/cylinder.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/physics_engines/pointmass3d/pointmass3d_engine.h>

namespace argos {

   static const Real     BODY_HEIGHT   = 0.090f;
   static const Real     BODY_SIDE     = 0.150f;
   static const Real     BODY_DIAGONAL = BODY_SIDE * ::sqrt(2);
   static const Real     BODY_RADIUS   = BODY_DIAGONAL / 2.0f;
   static const Real     BODY_MASS     = 5.0f;
   static const Real     BODY_INERTIA  = 0.01f;
   static const CVector3 POS_K_P(200.0f, 200.0f, 200.0f);
   static const CVector3 POS_K_D(50.0f, 50.0f, 50.0f);
   static const Real     YAW_K_P = 1.0f;
   static const Real     YAW_K_D = 0.0f;
   static const CVector3 VEL_K_P(100.0f, 100.0f, 100.0f);
   static const CVector3 VEL_K_D(50.0f, 50.0f, 50.0f);
   static const Real     ROT_K_P = 0.5f;
   static const Real     ROT_K_D = 0.1f;

   /****************************************/
   /****************************************/

   CPointMass3DCrazyflieModel::CPointMass3DCrazyflieModel(CPointMass3DEngine& c_engine,
                                                  CCrazyflieEntity& c_crazyflie) :
      CPointMass3DQuadRotorModel(c_engine,
                                 c_crazyflie.GetEmbodiedEntity(),
                                 c_crazyflie.GetQuadRotorEntity(),
                                 BODY_HEIGHT,
                                 BODY_RADIUS,
                                 BODY_MASS,
                                 BODY_INERTIA,
                                 POS_K_P,
                                 POS_K_D,
                                 YAW_K_P,
                                 YAW_K_D,
                                 VEL_K_P,
                                 VEL_K_D,
                                 ROT_K_P,
                                 ROT_K_D) {
      /* Register anchor update methods */
      RegisterAnchorMethod(GetEmbodiedEntity().GetAnchor("rab"),
                           &CPointMass3DCrazyflieModel::UpdateRABAnchor);
      RegisterAnchorMethod(GetEmbodiedEntity().GetAnchor("camera"),
                           &CPointMass3DCrazyflieModel::UpdateCameraAnchor);
   }

   /****************************************/
   /****************************************/

   void CPointMass3DCrazyflieModel::UpdateRABAnchor(SAnchor& s_anchor) {
      s_anchor.Orientation = GetEmbodiedEntity().GetOriginAnchor().Orientation;
      s_anchor.Position = s_anchor.OffsetPosition;
      s_anchor.Position += GetEmbodiedEntity().GetOriginAnchor().Position;
   }

   /****************************************/
   /****************************************/

   void CPointMass3DCrazyflieModel::UpdateCameraAnchor(SAnchor& s_anchor) {
      s_anchor.Orientation = GetEmbodiedEntity().GetOriginAnchor().Orientation;
      s_anchor.Orientation *= s_anchor.OffsetOrientation;
      s_anchor.Position = s_anchor.OffsetPosition;
      s_anchor.Position.Rotate(s_anchor.Orientation);
      s_anchor.Position += GetEmbodiedEntity().GetOriginAnchor().Position;
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_POINTMASS3D_OPERATIONS_ON_ENTITY(CCrazyflieEntity, CPointMass3DCrazyflieModel);

   /****************************************/
   /****************************************/

}
