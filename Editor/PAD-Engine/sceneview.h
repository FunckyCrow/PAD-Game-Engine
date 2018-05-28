#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QTreeWidget>
#include <PAD Engine/System/ECS/PADObject.h>
#include <scenenode.h>

class SceneView final : public QTreeWidget
{
    Q_OBJECT
public:
    pad::sys::ecs::PADObject* currentObject;

    SceneView(QWidget* parent = nullptr);
    SceneNode* AddObject(pad::sys::ecs::PADObject* obj, SceneNode* after = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

    void ParseScene();

private:
    void ParseObj(SceneNode* parent = nullptr);

private slots:
    void SetSelectedAsCurrent();

};

#endif // SCENEVIEW_H
