import Qt3D 2.0
import Qt3D.Renderer 2.0

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

    Entity
    {
        Mesh
        {
            id: chestMesh
            source: "qrc:/assets/Chest.obj"
            enabled: _settings.showModel
        }

        PhongMaterial
        {
            id: phongMaterial
            ambient: Qt.rgba( 0.6, 0.2, 0.1, 1 )
            diffuse: Qt.rgba( 0.2, 0.6, 0.1, 1 )
            specular: Qt.rgba( 0.2, 0.9, 0.1, 1 )
            shininess: 0.6
        }

        components: [ chestMesh, phongMaterial ]
    }

    Configuration
    {
        controlledCamera: camera
    }
}
