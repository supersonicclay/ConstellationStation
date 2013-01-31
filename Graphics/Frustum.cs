using Microsoft.DirectX;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Representation of a view frustum, that is a 4-sided pyramid with
    /// the top chopped off.
    /// </summary>
    public class Frustum
    {
        // Fields
        /// <summary>
        /// The bottom plane.
        /// </summary>
        public Plane Bottom;
        /// <summary>
        /// The far plane.
        /// </summary>
        public Plane Far;
        /// <summary>
        /// The left plane.
        /// </summary>
        public Plane Left;
        // The near plane.
        public Plane Near;
        /// <summary>
        /// The right plane.
        /// </summary>
        public Plane Right;
        /// <summary>
        /// The top plane.
        /// </summary>
	    public Plane Top;

        // Methods
        /// <summary>
        /// Returns <c>true</c> if this <see cref="T:Frustum"/> contains <paramref name="sphere"/>;
        /// otherwise <c>false</c>.
        /// </summary>
        /// <param name="sphere">A <see cref="T:BoundingSphere"/> to check.</param>
        /// <returns><c>true</c> if this <see cref="T:Frustum"/> contains <paramref name="sphere"/>;
        /// otherwise <c>false</c>.</returns>
        public bool ContainsSphere(BoundingSphere sphere)
        {
            Vector4 center4 = new Vector4(sphere.Center.X, sphere.Center.Y, sphere.Center.Z, 1.0f);
            return
                Left.Dot(center4) + sphere.Radius >= 0 &&
                Right.Dot(center4) + sphere.Radius >= 0 &&
                Top.Dot(center4) + sphere.Radius >= 0 &&
                Bottom.Dot(center4) + sphere.Radius >= 0 &&
                Near.Dot(center4) + sphere.Radius >= 0 &&
                Far.Dot(center4) + sphere.Radius >= 0;
        }
        /// <summary>
        /// Returns a new <see cref="T:Frustum"/> based on the combined view and projection matrices.
        /// </summary>
        /// <param name="viewProjectionMatrix">The view and projection matrices multiplied together (i.e. view * projection).</param>
        /// <returns>A new <see cref="T:Frustum"/> based on the combined view and projection matrices.</returns>
        public static Frustum FromCombinedMatrix(Matrix viewProjectionMatrix)
        {
            Plane left = new Plane();
            Plane right = new Plane();
            Plane top = new Plane();
            Plane bottom = new Plane();
            Plane near = new Plane();
            Plane far = new Plane();

            // Left plane
            left.A = viewProjectionMatrix.M14 + viewProjectionMatrix.M11;
            left.B = viewProjectionMatrix.M24 + viewProjectionMatrix.M21;
            left.C = viewProjectionMatrix.M34 + viewProjectionMatrix.M31;
            left.D = viewProjectionMatrix.M44 + viewProjectionMatrix.M41;

            // Right plane
            right.A = viewProjectionMatrix.M14 - viewProjectionMatrix.M11;
            right.B = viewProjectionMatrix.M24 - viewProjectionMatrix.M21;
            right.C = viewProjectionMatrix.M34 - viewProjectionMatrix.M31;
            right.D = viewProjectionMatrix.M44 - viewProjectionMatrix.M41;

            // Top plane
            top.A = viewProjectionMatrix.M14 - viewProjectionMatrix.M12;
            top.B = viewProjectionMatrix.M24 - viewProjectionMatrix.M22;
            top.C = viewProjectionMatrix.M34 - viewProjectionMatrix.M32;
            top.D = viewProjectionMatrix.M44 - viewProjectionMatrix.M42;

            // Bottom plane
            bottom.A = viewProjectionMatrix.M14 + viewProjectionMatrix.M12;
            bottom.B = viewProjectionMatrix.M24 + viewProjectionMatrix.M22;
            bottom.C = viewProjectionMatrix.M34 + viewProjectionMatrix.M32;
            bottom.D = viewProjectionMatrix.M44 + viewProjectionMatrix.M42;

            // Near plane
            near.A = viewProjectionMatrix.M13;
            near.B = viewProjectionMatrix.M23;
            near.C = viewProjectionMatrix.M33;
            near.D = viewProjectionMatrix.M43;

            // Far plane
            far.A = viewProjectionMatrix.M14 - viewProjectionMatrix.M13;
            far.B = viewProjectionMatrix.M24 - viewProjectionMatrix.M23;
            far.C = viewProjectionMatrix.M34 - viewProjectionMatrix.M33;
            far.D = viewProjectionMatrix.M44 - viewProjectionMatrix.M43;

            // Normalize planes
            left.Normalize();
            right.Normalize();
            top.Normalize();
            bottom.Normalize();
            near.Normalize();
            far.Normalize();

            return new Frustum() { Left = left, Right = right, Top = top, Bottom = bottom, Near = near, Far = far };
        }
        /// <summary>
        /// Returns a new <see cref="T:Frustum"/> based on the given view and projection matrices.
        /// </summary>
        /// <param name="view">The view matrix.</param>
        /// <param name="projection">The projection matrix.</param>
        /// <returns>A new <see cref="T:Frustum"/> based on the given view and projection matrices.</returns>
        public static Frustum FromViewProjMatrices(Matrix view, Matrix projection)
        {
            return FromCombinedMatrix(view * projection);
        }
    }
}
