/**
 * @file <argos3/plugins/simulator/entities/tag_equipped_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "tag_equipped_entity.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/media/tag_medium.h>

namespace argos {

   /****************************************/
   /****************************************/

   CTagEquippedEntity::SInstance::SInstance(CTagEntity& c_tag,
                                            SAnchor& s_anchor,
                                            const CVector3& c_position_offset,
                                            const CQuaternion& c_orientation_offset) :
      Tag(c_tag),
      Anchor(s_anchor),
      PositionOffset(c_position_offset),
      OrientationOffset(c_orientation_offset) {}

   /****************************************/
   /****************************************/

   CTagEquippedEntity::CTagEquippedEntity(CComposableEntity* pc_parent) :
      CComposableEntity(pc_parent) {
      Disable();
   }

   /****************************************/
   /****************************************/

   CTagEquippedEntity::CTagEquippedEntity(CComposableEntity* pc_parent,
                                          const std::string& str_id) :
      CComposableEntity(pc_parent, str_id) {
      Disable();
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* Init parent */
         CComposableEntity::Init(t_tree);
         /* Go through the tag entries */
         TConfigurationNodeIterator itTag("tag");
         for(itTag = itTag.begin(&t_tree);
             itTag != itTag.end();
             ++itTag) {
            /* Initialise the Tag using the XML */
            CTagEntity* pcTag = new CTagEntity(this);
            pcTag->Init(*itTag);
            CVector3 cPositionOffset;
            GetNodeAttribute(*itTag, "position", cPositionOffset);
            CQuaternion cOrientationOffset;
            GetNodeAttribute(*itTag, "orientation", cOrientationOffset);
            /* Parse and look up the anchor */
            std::string strAnchorId;
            GetNodeAttribute(*itTag, "anchor", strAnchorId);
            /*
             * NOTE: here we get a reference to the embodied entity
             * This line works under the assumption that:
             * 1. the TagEquippedEntity has a parent;
             * 2. the parent has a child whose id is "body"
             * 3. the "body" is an embodied entity
             * If any of the above is false, this line will bomb out.
             */
            CEmbodiedEntity& cBody = GetParent().GetComponent<CEmbodiedEntity>("body");
            /* Add the tag to this container */
            m_vecInstances.emplace_back(*pcTag,
                                        cBody.GetAnchor(strAnchorId),
                                        cPositionOffset,
                                        cOrientationOffset);
            AddComponent(*pcTag);
         }
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize tag equipped entity \"" <<
                                     GetContext() + GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::Reset() {
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Tag.Reset();
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::Enable() {
      CEntity::Enable();
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Anchor.Enable();
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::Disable() {
      CEntity::Disable();
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Anchor.Disable();
      }
   }

   /****************************************/
   /****************************************/

   CTagEntity& CTagEquippedEntity::GetTag(UInt32 un_index) {
      ARGOS_ASSERT(un_index < m_vecInstances.size(),
                   "CTagEquippedEntity::GetTag(), id=\"" <<
                   GetContext() + GetId() <<
                   "\": index out of bounds: un_index = " <<
                   un_index <<
                   ", m_vecInstances.size() = " <<
                   m_vecInstances.size());
      return m_vecInstances[un_index].Tag;
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::SetTagPayload(UInt32 un_index,
                                          const std::string& str_payload) {
      ARGOS_ASSERT(un_index < m_vecInstances.size(),
                   "CTagEquippedEntity::SetTagPayload(), id=\"" <<
                   GetContext() + GetId() <<
                   "\": index out of bounds: un_index = " <<
                   un_index <<
                   ", m_vecInstances.size() = " <<
                   m_vecInstances.size());
      m_vecInstances[un_index].Tag.SetPayload(str_payload);
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::SetTagPayloads(const std::string& str_payload) {
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Tag.SetPayload(str_payload);
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::SetTagPayloads(const std::vector<std::string>& vec_payloads) {
      if(vec_payloads.size() == m_vecInstances.size()) {
         for(UInt32 i = 0; i < vec_payloads.size(); ++i) {
            m_vecInstances[i].Tag.SetPayload(vec_payloads[i]);
         }
      }
      else {
         THROW_ARGOSEXCEPTION(
            "CTagEquippedEntity::SetTagPayloads(), id=\"" <<
            GetContext() + GetId() <<
            "\": number of tags (" <<
            m_vecInstances.size() <<
            ") does not equal the passed payload vector size (" <<
            vec_payloads.size() <<
            ")");
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::UpdateComponents() {
      /* Tag position wrt global reference frame */
      CVector3 cTagPosition;
      CQuaternion cTagOrientation;
      for(SInstance& s_instance : m_vecInstances) {
         if(s_instance.Tag.IsEnabled()) {
            cTagPosition = s_instance.PositionOffset;
            cTagPosition.Rotate(s_instance.Anchor.Orientation);
            cTagPosition += s_instance.Anchor.Position;
            cTagOrientation = s_instance.Anchor.Orientation *
               s_instance.OrientationOffset;
            s_instance.Tag.MoveTo(cTagPosition, cTagOrientation);
         }
      }
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::AddToMedium(CTagMedium& c_medium) {
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Tag.AddToMedium(c_medium);
      }
      Enable();
   }

   /****************************************/
   /****************************************/

   void CTagEquippedEntity::RemoveFromMedium() {
      for(SInstance& s_instance : m_vecInstances) {
         s_instance.Tag.RemoveFromMedium();
      }
      Disable();
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CTagEquippedEntity);

   /****************************************/
   /****************************************/

}
