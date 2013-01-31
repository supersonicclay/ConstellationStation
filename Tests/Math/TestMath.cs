using ConstellationStation.Common;
using Microsoft.DirectX;
using NUnit.Framework;

namespace ConstellationStation.Math
{
    [TestFixture]
    public class TestMath
    {
        private const float DELTA = 0.01f;
        [Test]
        public void TestDegreesToRadians()
        {
            Assert.AreEqual(0.0f, Angles.DegreesToRadians(0.0f), DELTA);
            Assert.AreEqual((float)(System.Math.PI / 4), Angles.DegreesToRadians(45.0f), DELTA);
            Assert.AreEqual((float)(System.Math.PI / 2), Angles.DegreesToRadians(90.0f), DELTA);
            Assert.AreEqual((float)(System.Math.PI), Angles.DegreesToRadians(180.0f), DELTA);
            Assert.AreEqual((float)(System.Math.PI * 1.5), Angles.DegreesToRadians(270.0f), DELTA);
            Assert.AreEqual((float)(System.Math.PI * 2), Angles.DegreesToRadians(360.0f), DELTA);
        }

        [Test]
        public void TestRadiansToDegrees()
        {
            Assert.AreEqual(0.0f, Angles.RadiansToDegrees(0.0f), DELTA);
            Assert.AreEqual(45.0f, Angles.RadiansToDegrees((float)(System.Math.PI / 4)), DELTA);
            Assert.AreEqual(90.0f, Angles.RadiansToDegrees((float)(System.Math.PI / 2)), DELTA);
            Assert.AreEqual(180.0f, Angles.RadiansToDegrees((float)(System.Math.PI)), DELTA);
            Assert.AreEqual(270.0f, Angles.RadiansToDegrees((float)(System.Math.PI * 1.5)), DELTA);
            Assert.AreEqual(360.0f, Angles.RadiansToDegrees((float)(System.Math.PI * 2)), DELTA);
        }

        [Test]
        public void TestVector3FromSpherical()
        {
            Vector3 vec;
            SphericalCoordinates spherical = new SphericalCoordinates();

            // When phi is 0, doesn't matter what theta is
            spherical.Phi = 0.0f;
            for (spherical.Theta = 0.0f; spherical.Theta < System.Math.PI * 2; spherical.Theta += 0.01f)
            {
                Angles.Vector3FromSpherical(out vec, spherical);
                Assert.AreEqual(0.0f, vec.X, DELTA);
                Assert.AreEqual(1.0f, vec.Y, DELTA);
                Assert.AreEqual(0.0f, vec.Z, DELTA);
            }

            spherical.Phi = (float)(System.Math.PI / 2);
            spherical.Theta = 0.0f;
            Angles.Vector3FromSpherical(out vec, spherical);
            Assert.AreEqual(0.0f, vec.X, DELTA);
            Assert.AreEqual(0.0f, vec.Y, DELTA);
            Assert.AreEqual(1.0f, vec.Z, DELTA);

            spherical.Phi = (float)(System.Math.PI / 2);
            spherical.Theta = (float)(System.Math.PI / 2);
            Angles.Vector3FromSpherical(out vec, spherical);
            Assert.AreEqual(1.0f, vec.X, DELTA);
            Assert.AreEqual(0.0f, vec.Y, DELTA);
            Assert.AreEqual(0.0f, vec.Z, DELTA);

            spherical.Phi = (float)(System.Math.PI / 2);
            spherical.Theta = (float)(System.Math.PI * 1.5);
            Angles.Vector3FromSpherical(out vec, spherical);
            Assert.AreEqual(-1.0f, vec.X, DELTA);
            Assert.AreEqual(0.0f, vec.Y, DELTA);
            Assert.AreEqual(0.0f, vec.Z, DELTA);

            spherical.Phi = 2.23f;
            spherical.Theta = 3.86f;
            Angles.Vector3FromSpherical(out vec, spherical);
            Assert.AreEqual(-0.5203f, vec.X, DELTA);
            Assert.AreEqual(-0.6125f, vec.Y, DELTA);
            Assert.AreEqual(-0.5951f, vec.Z, DELTA);
        }

        [Test]
        public void TestSphericalFromVector3()
        {
            SphericalCoordinates spherical;
            Vector3 vec;

            vec = new Vector3(0.0f, 1.0f, 0.0f);
            Angles.SphericalFromVector3(out spherical, vec);
            Assert.AreEqual(0.0f, spherical.Phi, DELTA);
            Assert.AreEqual(0.0f, spherical.Theta, DELTA);

            vec = new Vector3(0.0f, 0.0f, 1.0f);
            Angles.SphericalFromVector3(out spherical, vec);
            Assert.AreEqual((float)(System.Math.PI / 2), spherical.Phi, DELTA);
            Assert.AreEqual(0.0f, spherical.Theta, DELTA);

            vec = new Vector3(1.0f, 0.0f, 0.0f);
            Angles.SphericalFromVector3(out spherical, vec);
            Assert.AreEqual((float)(System.Math.PI / 2), spherical.Phi, DELTA);
            Assert.AreEqual((float)(System.Math.PI / 2), spherical.Theta, DELTA);

            vec = new Vector3(-1.0f, 0.0f, 0.0f);
            Angles.SphericalFromVector3(out spherical, vec);
            Assert.AreEqual((float)(System.Math.PI / 2), spherical.Phi, DELTA);
            Assert.AreEqual((float)(System.Math.PI * 1.5), spherical.Theta, DELTA);

            vec = new Vector3(-0.5203f, -0.6125f, -0.5951f);
            Angles.SphericalFromVector3(out spherical, vec);
            Assert.AreEqual(2.23f, spherical.Phi, DELTA);
            Assert.AreEqual(3.86f, spherical.Theta, DELTA);
        }

        [Test]
        public void TestSphericalFromEquatorial()
        {
            SphericalCoordinates spherical;
            EquitorialCoordinates equitorial;

            equitorial = new EquitorialCoordinates()
            {
                RightAscension = new RightAscension() { Hours = 0, Minutes = 0, Seconds = 0.0f },
                Declination = new Declination() { Positive = true, Degrees = 90, Minutes = 0, Seconds = 0.0f }
            };
            Angles.SphericalFromEquatorial(out spherical, equitorial);
            Assert.AreEqual(0.0f, spherical.Phi, DELTA);
            Assert.AreEqual(0.0f, spherical.Theta, DELTA);

            equitorial = new EquitorialCoordinates()
            {
                RightAscension = new RightAscension() { Hours = 12, Minutes = 0, Seconds = 0.0f },
                Declination = new Declination() { Positive = false, Degrees = 0, Minutes = 0, Seconds = 0.0f }
            };
            Angles.SphericalFromEquatorial(out spherical, equitorial);
            Assert.AreEqual((float)(System.Math.PI * 0.5), spherical.Phi, DELTA);
            Assert.AreEqual((float)System.Math.PI, spherical.Theta, DELTA);

            equitorial = new EquitorialCoordinates()
            {
                RightAscension = new RightAscension() { Hours = 18, Minutes = 0, Seconds = 0.0f },
                Declination = new Declination() { Positive = false, Degrees = 45, Minutes = 0, Seconds = 0.0f }
            };
            Angles.SphericalFromEquatorial(out spherical, equitorial);
            Assert.AreEqual((float)(System.Math.PI * 0.75), spherical.Phi, DELTA);
            Assert.AreEqual((float)(System.Math.PI * 0.5), spherical.Theta, DELTA);

            equitorial = new EquitorialCoordinates()
            {
                RightAscension = new RightAscension() { Hours = 3, Minutes = 2, Seconds = 14.2f },
                Declination = new Declination() { Positive = false, Degrees = 38, Minutes = 4, Seconds = 21.8f }
            };
            Angles.SphericalFromEquatorial(out spherical, equitorial);
            Assert.AreEqual(2.23529077f, spherical.Phi, DELTA);
            Assert.AreEqual(5.48802805f, spherical.Theta, DELTA);
        }

        [Test]
        public void TestEquatorialFromSpherical()
        {
            SphericalCoordinates spherical;
            EquitorialCoordinates equitorial;

            spherical = new SphericalCoordinates()
            {
                Phi = 0.0f,
                Theta = 0.0f
            };
            Angles.EquatorialFromSpherical(out equitorial, spherical);
            Assert.AreEqual(0, equitorial.RightAscension.Hours);
            Assert.AreEqual(0, equitorial.RightAscension.Minutes);
            Assert.AreEqual(0.0f, equitorial.RightAscension.Seconds, DELTA);
            Assert.AreEqual(true, equitorial.Declination.Positive);
            Assert.AreEqual(90, equitorial.Declination.Degrees);
            Assert.AreEqual(0, equitorial.Declination.Minutes);
            Assert.AreEqual(0.0f, equitorial.Declination.Seconds, DELTA);

            spherical = new SphericalCoordinates()
            {
                Phi = (float)(System.Math.PI * 0.5),
                Theta = (float)System.Math.PI
            };
            Angles.EquatorialFromSpherical(out equitorial, spherical);
            Assert.AreEqual(12, equitorial.RightAscension.Hours);
            Assert.AreEqual(0, equitorial.RightAscension.Minutes);
            Assert.AreEqual(0.0f, equitorial.RightAscension.Seconds, DELTA);
            Assert.AreEqual(true, equitorial.Declination.Positive);
            Assert.AreEqual(0, equitorial.Declination.Degrees);
            Assert.AreEqual(0, equitorial.Declination.Minutes);
            Assert.AreEqual(0.0f, equitorial.Declination.Seconds, DELTA);

            spherical = new SphericalCoordinates()
            {
                Phi = (float)(System.Math.PI * 0.75),
                Theta = (float)(System.Math.PI * 0.5)
            };
            Angles.EquatorialFromSpherical(out equitorial, spherical);
            Assert.AreEqual(18, equitorial.RightAscension.Hours);
            Assert.AreEqual(0, equitorial.RightAscension.Minutes);
            Assert.AreEqual(0.0f, equitorial.RightAscension.Seconds, DELTA);
            Assert.AreEqual(false, equitorial.Declination.Positive);
            Assert.AreEqual(45, equitorial.Declination.Degrees);
            Assert.AreEqual(0, equitorial.Declination.Minutes);
            Assert.AreEqual(0.0f, equitorial.Declination.Seconds, DELTA);

            spherical = new SphericalCoordinates()
            {
                Phi = 2.23529077f,
                Theta = 5.48802805f
            };
            Angles.EquatorialFromSpherical(out equitorial, spherical);
            Assert.AreEqual(3, equitorial.RightAscension.Hours);
            Assert.AreEqual(2, equitorial.RightAscension.Minutes);
            Assert.AreEqual(14.2f, equitorial.RightAscension.Seconds, DELTA);
            Assert.AreEqual(false, equitorial.Declination.Positive);
            Assert.AreEqual(38, equitorial.Declination.Degrees);
            Assert.AreEqual(4, equitorial.Declination.Minutes);
            Assert.AreEqual(21.8f, equitorial.Declination.Seconds, DELTA);
        }
    }
}
