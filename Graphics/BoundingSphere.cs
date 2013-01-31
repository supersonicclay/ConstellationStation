using Microsoft.DirectX;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Representation of a bounding sphere with a center and radius.
    /// </summary>
    public struct BoundingSphere
    {
        // Fields
        /// <summary>
        /// The 3-dimensional center of the sphere.
        /// </summary>
        public Vector3 Center;
        /// <summary>
        /// The radius of the sphere.
        /// </summary>
        public float Radius;
    }
}
