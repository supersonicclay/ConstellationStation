using ConstellationStation.Common;
using ConstellationStation.Graphics;
using Microsoft.DirectX;
using NUnit.Framework;

namespace ConstellationStation
{
    [TestFixture]
    public class TestAssertExtensions
    {
        private const float DELTA = 0.001f;

        [Test]
        public void TestVector3AreEqual()
        {
            AssertX.AreEqual(new Vector3(1.0f, 4.0f, 3.842f), new Vector3(1.00001f, 3.99999f, 3.84199999f), DELTA);
        }

        [Test]
        public void TestPlaneAreEqual()
        {
            AssertX.AreEqual(new Plane(1.0f, 2.0f, 3.4f, 7.95f), new Plane(1.0f, 2.0001f, 3.399999f, 7.95000001f), DELTA);
        }

        [Test]
        public void TestFrustumAreEqual()
        {
            Plane left1 = new Plane(2.0f, 3.0f, 4.1f, 1.0f);
            Plane left2 = new Plane(2.0f, 3.0f, 4.1f, 1.0f);
            Plane right1 = new Plane(1.0f, 2.0f, 3.4f, 7.95f);
            Plane right2 = new Plane(1.0f, 2.0f, 3.4f, 7.95f);
            Plane top1 = new Plane(1.0f, 1.0f, 1.0f, 1.0f);
            Plane top2 = new Plane(1.0f, 1.0f, 1.0f, 1.0f);
            Plane bottom1 = new Plane(8.3f, 2.22f, 1.0f, 0.0f);
            Plane bottom2 = new Plane(8.3f, 2.22f, 1.0f, 0.0f);
            Plane near1 = new Plane(3.0f, 3.0f, 3.0f, 3.0f);
            Plane near2 = new Plane(3.0f, 3.0f, 3.0f, 3.0f);
            Plane far1 = new Plane(2.0f, 2.0f, 2.0f, 2.0f);
            Plane far2 = new Plane(2.0f, 2.0f, 2.0f, 2.0f);
            Frustum f1 = new Frustum()
            {
                Left = left1,
                Right = right1,
                Top = top1,
                Bottom = bottom1,
                Near = near1,
                Far = far1
            };
            Frustum f2 = new Frustum()
            {
                Left = left2,
                Right = right2,
                Top = top2,
                Bottom = bottom2,
                Near = near2,
                Far = far2
            };

            AssertX.AreEqual(f1, f2, DELTA);
        }

        [Test]
        public void TestRightAscensionAreEqual()
        {
            RightAscension ra1 = new RightAscension() { Hours = 3, Minutes = 4, Seconds = 5.09f };
            RightAscension ra2 = new RightAscension() { Hours = 3, Minutes = 4, Seconds = 5.089999f };
            AssertX.AreEqual(ra1, ra2, 0.001f);
        }

        [Test]
        public void TestDeclinationAreEqual()
        {
            Declination dec1 = new Declination() { Positive = true, Degrees = 23, Minutes = 41, Seconds = 25.0f };
            Declination dec2 = new Declination() { Positive = true, Degrees = 23, Minutes = 41, Seconds = 25.0f };
            AssertX.AreEqual(dec1, dec2, 0.1f);
        }
    }
}
