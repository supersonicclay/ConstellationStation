using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Representation of a star vertex.
    /// </summary>
    public struct StarVertex
    {
        // Constants
        /// <summary>
        /// The vertex format used by star vertices.
        /// </summary>
        public const VertexFormats Format = VertexFormats.Position | VertexFormats.PointSize | VertexFormats.Diffuse;

        // Fields
        /// <summary>
        /// The 3d position of the star.
        /// </summary>
        public Vector3 Position;
        /// <summary>
        /// The point size of the star.
        /// </summary>
        public float PointSize;
        /// <summary>
        /// The color of the star.
        /// </summary>
        public int Color;
    }
}
