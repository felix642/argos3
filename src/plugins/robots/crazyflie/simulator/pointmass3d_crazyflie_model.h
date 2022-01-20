/**
 * @file <argos3/plugins/robots/foot-bot/simulator/pointmass3d_crazyflie_model.h>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#ifndef POINTMASS3D_CRAZYFLIE_H
#define POINTMASS3D_CRAZYFLIE_H

namespace argos {
   class CPointMass3DEngine;
   class CPointMass3DQuadRotorModel;
   class CPointMass3DCrazyflieModel;
   class CQuadRotorEntity;
}

#include <argos3/plugins/simulator/physics_engines/pointmass3d/pointmass3d_quadrotor_model.h>
#include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>

namespace argos {

   class CPointMass3DCrazyflieModel : public CPointMass3DQuadRotorModel {

   public:
      
      CPointMass3DCrazyflieModel(CPointMass3DEngine& c_engine,
                             CCrazyflieEntity& c_crazyflie);
      virtual ~CPointMass3DCrazyflieModel() {}

   private:

      void UpdateRABAnchor(SAnchor& s_anchor);
      
      void UpdateCameraAnchor(SAnchor& s_anchor);
      
   };

}

#endif
