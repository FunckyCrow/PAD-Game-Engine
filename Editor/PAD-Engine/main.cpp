#include <QApplication.h>
#include <QFile>
#include <QTextStream>

#include <padeditor.h>
#include <glwidget.h>
#include "ui_padeditor.h"

#include <AssetParser/AssetParser.h>
#include <AssetParser/AssetReader.h>

//#include <EnginePCH.h>
#include <Core/EngineDLL.h>
//#include <Graphics/GL/Shader/GLShaderProgram.h>
//#include <Graphics/GL/Shader/GLVertexShader.h>
//#include <Graphics/GL/Shader/GLFragmentShader.h>
//#include <System/ECS/PerspectiveCamera.h>
//#include <System/ECS/PADObject.h>
//#include <System/ECS/RigidBody.h>
//#include <Graphics/Model/Mesh.h>
//#include <Graphics/Model/MeshData.h>
//#include <System/ECS/MeshRenderer.h>
//#include <System/ECS/BoxCollider.h>
//#include <AssetParser/AssetReader.h>
//#include <AssetParser/AssetParser.h>

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    PADEditor w;
    w.show();
    pad::parser::ParseFile("../Resources/FBX/GiantSpider.fbx", "../Resources/PADFormat/");

    #pragma region RenderInit

    pad::gfx::win::WindowSettings winSettings;

    winSettings.title			= "This is a SDL Window.";
    winSettings.position.x		= 0u;
    winSettings.position.y		= 30u;
    winSettings.size.x			= 1600u;
    winSettings.size.y			= 900u;
    winSettings.isFullscreen	= false;
    winSettings.windowType		= pad::gfx::win::E_WINDOW_TYPE::QT;

    // Will be read from a config file
    pad::gfx::rhi::ContextSettings contextSettings;

    contextSettings.viewportSize.x		= winSettings.size.x;
    contextSettings.viewportSize.y		= winSettings.size.y;
    contextSettings.clearColor.r		= 150.f / 255.f;
    contextSettings.clearColor.g		= 150.f / 255.f;
    contextSettings.clearColor.b		= 150.f / 255.f;
    contextSettings.clearColor.a		= 1.0f;
    contextSettings.implementationType	= pad::gfx::rhi::E_RENDERER_IMPLEMENTATION_TYPE::OPENGL;
    contextSettings.cullFace			= pad::gfx::rhi::E_CULL_FACE::BACK;
    contextSettings.depthFunc			= pad::gfx::rhi::E_DEPTH_FUNCTION::LESS;
    contextSettings.windingOrder		= pad::gfx::rhi::E_WINDING_ORDER::COUNTER_CLOCKWISE;
    contextSettings.enabledBuffers		= pad::gfx::rhi::BufferType::ALL;

    #pragma endregion

    pad::CreateEngine();
    pad::InitEngine(contextSettings, winSettings);

    pad::sys::ecs::PADObject* plat = pad::CreatePADObject("Platform");
    plat->AddComponent<pad::sys::ecs::MeshRenderer>("Cube", "Default");

    pad::LoadResourceFile("../Resources/PADFormat/creature_pitlord_magtheridon_0.PADMaterial", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_pitlord_magtheridon.PADMesh", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_0.PADMaterial", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider.PADMesh", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_Walk [0].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_AttackUnarmed [4].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_CombatWound [5].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_Run [1].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_SpellCast [7].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_Stand [2].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider_Death [6].PADAnim", "");
    pad::LoadResourceFile("../Resources/PADFormat/creature_giantspider_giantspider.PADSkeleton", "");
    pad::LoadResourceFile("../Resources/PADFormat/Grid.PADMaterial", "");
    pad::LoadResourceFile("../Resources/PADFormat/Default.PADMaterial", "");
    pad::LoadResourceFile("../Resources/PADFormat/pCube1.PADMesh", "");
    pad::LoadResourceFile("../Resources/PADFormat/lambert2.PADMaterial", "");

    plat->GetTransform().SetScale(pad::math::Vec3f(10.f, 1.f, 10.f));

    pad::sys::ecs::MeshRenderer* mr = plat->GetComponent<pad::sys::ecs::MeshRenderer>();

    plat->AddComponent<pad::sys::ecs::BoxCollider>(pad::math::Vec3f(10.f, 1.f, 10.f));
    plat->AddComponent<pad::sys::ecs::RigidBody>();
    pad::sys::ecs::RigidBody* rb = plat->GetComponent<pad::sys::ecs::RigidBody>();
    rb->SetMass(0.f);

    for (int i = 0; i < 1; ++i)
    {
        pad::sys::ecs::PADObject* cube = pad::CreatePADObject(std::string("Cube_0") + std::to_string(i));

        cube->GetTransform().SetPosition(pad::math::Vec3f(0, i*10, 0));
        cube->GetTransform().SetRotation(pad::math::Vec3f(0, 90, 0));
        cube->GetTransform().SetScale(0.03f);

        cube->AddComponent<pad::sys::ecs::AnimRenderer>(
            "creature_giantspider_giantspider",
            "creature_giantspider_giantspider_0",
            "creature_giantspider_giantspider",
            "creature_giantspider_giantspider_AttackUnarmed [3]");
        cube->AddComponent<pad::sys::ecs::BoxCollider>(pad::math::Vec3f(1.f, 1.f, 1.f));
        cube->AddComponent<pad::sys::ecs::RigidBody>();

        cube->GetComponent<pad::sys::ecs::AnimRenderer>()->SetAnim("creature_giantspider_giantspider_Run [1]");
        cube->GetComponent<pad::sys::ecs::AnimRenderer>()->GetSettings().isAffectedByLight = true;
        cube->GetComponent<pad::sys::ecs::AnimRenderer>()->SetAnimSpeed(3);
        cube->GetComponent<pad::sys::ecs::AnimRenderer>()->SetLoop(true);

        rb = cube->GetComponent<pad::sys::ecs::RigidBody>();
        rb->SetMass(10.f);
    }

    pad::sys::ecs::PADObject* grid = pad::CreatePADObject("Grid");
    grid->AddComponent<pad::sys::ecs::MeshRenderer>("Quad", "Grid");
    grid->GetTransform().SetRotation(pad::math::Vec3f(-90.f, 0.f, 0.f));
    grid->GetTransform().SetScale(100.f);

    pad::StartSimulation();
    a.exec();
    return pad::DestroyEngine();;
}