/**
 * @file <argos3/plugins/robots/crazyflie/simulator/qtopengl_crazyflie.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "qtopengl_crazyflie.h"
#include "crazyflie_entity.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_obj_model.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

namespace argos {

   /****************************************/
   /****************************************/

   class CQTOpenGLOperationDrawCrazyflieNormal : public CQTOpenGLOperationDrawNormal {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CCrazyflieEntity& c_entity) {
         static CQTOpenGLObjModel m_cCrazyflieModel("cf2.obj");
         c_visualization.DrawRays(c_entity.GetControllableEntity());
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         m_cCrazyflieModel.Draw();
      }
   };

   /****************************************/
   /****************************************/

   class CQTOpenGLOperationDrawCrazyflieSelected : public CQTOpenGLOperationDrawSelected {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CCrazyflieEntity& c_entity) {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawCrazyflieNormal, CCrazyflieEntity);

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawCrazyflieSelected, CCrazyflieEntity);

   /****************************************/
   /****************************************/

}
