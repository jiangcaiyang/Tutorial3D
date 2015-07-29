import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity
{
    id: root

    components: FrameGraph
    {
        ForwardRenderer
        {
            clearColor: Qt.rgba( 0.2, 0, 0, 1 )
        }
    }
}
