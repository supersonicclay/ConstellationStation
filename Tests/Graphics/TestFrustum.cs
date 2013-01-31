using Microsoft.DirectX;
using NUnit.Framework;

namespace ConstellationStation.Graphics
{
    [TestFixture]
    public class TestFrustum
    {
        private const float DELTA = 0.01f;

        private Matrix view;
        private Matrix projection;

        [Test]
        public void TestFromMatrix()
        {
            view = Matrix.Identity;
            projection = Matrix.PerspectiveFovLH((float)(System.Math.PI / 4), 1.0f, 0.8f, 100.0f);

            Frustum frustum1 = Frustum.FromViewProjMatrices(view, projection);
            Frustum frustum2 = Frustum.FromCombinedMatrix(view * projection);

	        Plane left = new Plane(0.9238796f, 0.0f, 0.3826835f, 0.0f);
            Plane right = new Plane(-0.9238796f, 0.0f, 0.3826835f, 0.0f);
            Plane top = new Plane(0.0f, -0.9238796f, 0.3826835f, 0.0f);
            Plane bottom = new Plane(0.0f, 0.9238796f, 0.3826835f, 0.0f);
	        Plane near = new Plane(0.0f, 0.0f, 1.0f, -0.8f);
	        Plane far = new Plane(0.0f, 0.0f, -1.0f, 100.0f);
            Frustum frustumExpected = new Frustum()
            {
                Left = left,
                Right = right,
                Top = top,
                Bottom = bottom,
                Near = near,
                Far = far
            };

            AssertX.AreEqual(frustum1, frustum2, DELTA);
            AssertX.AreEqual(frustumExpected, frustum1, DELTA);
        }

        [Test]
        public void TestSphereInFrustum()
        {
            view = Matrix.Identity;
            projection = Matrix.PerspectiveFovLH((float)(System.Math.PI / 4), 1.0f, 0.8f, 100.0f);

            Frustum frustum = Frustum.FromViewProjMatrices(view, projection);

            bool b1 = frustum.ContainsSphere(new BoundingSphere() { Center = new Vector3(0.0f, 0.0f, 1.0f), Radius = 0.0001f });
            bool b2 = frustum.ContainsSphere(new BoundingSphere() { Center = new Vector3(0.0001f, -0.003f, 1.0f), Radius = 0.001f });
            bool b3 = frustum.ContainsSphere(new BoundingSphere() { Center = new Vector3(1.0f, 0.0f, 0.0f), Radius = 0.0001f });

            Assert.IsTrue(b1);
            Assert.IsTrue(b2);
            Assert.IsFalse(b3);
        }
    }
}
