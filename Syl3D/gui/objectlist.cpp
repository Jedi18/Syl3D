#include "objectlist.h"
#include "../entity/entityfactory.h"
#include "../entity/entitycontainer.h"
#include "objectinfovisitor.h"

using namespace gui;

bool ObjectList::open = false;
int ObjectList::selectedObject = -1;

void ObjectList::ShowObjectList() {
    if (!ObjectList::open) {
        return;
    }

    std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
    std::vector<std::shared_ptr<Object>> objectList = entityContainer->objectList();

    ObjectInfoVisitor::ObjectInfo objectInfo;
    ObjectInfoVisitor objectInfoVisitor;

    ImGui::Begin("Objects", &open);

    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth
        | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;

    for (const std::shared_ptr<Object> object : objectList) {
        int id = object->id();
        ImGuiTreeNodeFlags node_flags = base_flags;
        const bool is_selected = (selectedObject == object->id());
        if (is_selected)
            node_flags |= ImGuiTreeNodeFlags_Selected;

        std::shared_ptr<entity::Entity> selectedEntity = std::dynamic_pointer_cast<entity::Entity>(object);
        if (selectedEntity != nullptr) {
            selectedEntity->accept(objectInfoVisitor);
            objectInfo = objectInfoVisitor.getData();
        }
        else {
            std::shared_ptr<light::Light> selectedLight = std::dynamic_pointer_cast<light::Light>(object);
            selectedLight->accept(objectInfoVisitor);
            objectInfo = objectInfoVisitor.getData();
        }

        std::string entityName = objectInfo.entityTypeName;
        entityName += " ID:%d";

        // Uncomment after entity relationships are implemented 

        /*bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)id, node_flags, entityName.c_str(), id);
        if (ImGui::IsItemClicked()) {
            selectedObject = id;
        }

        if (node_open)
        {
            ImGui::BulletText("Blah blah\nBlah Blah");
            ImGui::TreePop();
        }*/

        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
        ImGui::TreeNodeEx((void*)(intptr_t)id, node_flags, entityName.c_str(), id);
        if (ImGui::IsItemClicked()) {
            selectedObject = id;
            std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
            entityContainer->setSelectedObject(selectedObject);
        }
    }
 
    ImGui::End();
}

void ObjectList::setSelectedObject(int selectedObjectId) {
    selectedObject = selectedObjectId;
}