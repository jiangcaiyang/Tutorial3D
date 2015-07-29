import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick 2.5 as Quick

Entity
{
    id: root

    Camera
    {
        id: camera
        position: Qt.vector3d( 0.0, 20.0, 100.0 )
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16.0 / 9.0
        nearPlane : 0.1
        farPlane : 1000.0
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 20.0, 0.0 )
    }

    components: FrameGraph
    {
        ForwardRenderer
        {
            clearColor: Qt.rgba( 0.2, 0, 0, 1 )
            camera: camera
        }
    }

    PhongMaterial
    {
        id: phongMaterial
        ambient: _settings.ambient
        diffuse: _settings.diffuse
        specular: _settings.specular
        shininess: _settings.shininess
    }

    Entity
    {
        Mesh
        {
            id: chestMesh
            source: "qrc:/assets/Chest.obj"
            enabled: _settings.showModel
        }

        components: [ chestMesh, phongMaterial ]
    }

    Entity
    {
        Mesh
        {
            id: trefoilMesh
            source: "qrc:/assets/trefoil.obj"
            enabled: _settings.showModel
        }

        Transform
        {
            id: transform

            Translate
            {
                translation: Qt.vector3d( 0, 30, 50 )
            }

            Rotate
            {
                axis: Qt.vector3d( 0, 1, 0 )
                Quick.NumberAnimation on angle
                {
                    from: 0
                    to: 360
                    loops: Quick.Animation.Infinite
                    duration: 2000
                    running: true
                }
            }
        }

        components: [ trefoilMesh, phongMaterial, transform ]
    }

    Configuration
    {
        controlledCamera: camera
    }
}
