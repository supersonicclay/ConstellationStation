using ConstellationStation.Common;
using ConstellationStation.Graphics;
using Microsoft.DirectX;
using NUnit.Framework;

namespace ConstellationStation
{
    public class AssertX
    {
        public static void AreEqual(Vector3 expected, Vector3 actual, float delta)
        {
            Assert.AreEqual(expected.X, actual.X, delta, "X");
            Assert.AreEqual(expected.Y, actual.Y, delta, "Y");
            Assert.AreEqual(expected.Z, actual.Z, delta, "Z");
        }

        public static void AreEqual(Plane expected, Plane actual, float delta)
        {
            Assert.AreEqual(expected.A, actual.A, delta, "A");
            Assert.AreEqual(expected.B, actual.B, delta, "B");
            Assert.AreEqual(expected.C, actual.C, delta, "C");
            Assert.AreEqual(expected.D, actual.D, delta, "D");
        }

        public static void AreEqual(RightAscension expected, RightAscension actual, float delta)
        {
            Assert.AreEqual(expected.Hours, actual.Hours, "Hours");
            Assert.AreEqual(expected.Minutes, actual.Minutes, "Minutes");
            Assert.AreEqual(expected.Seconds, actual.Seconds, delta, "Seconds");
        }

        public static void AreEqual(Declination expected, Declination actual, float delta)
        {
            Assert.AreEqual(expected.Positive, actual.Positive, "Positive");
            Assert.AreEqual(expected.Degrees, actual.Degrees, "Degrees");
            Assert.AreEqual(expected.Minutes, actual.Minutes, "Minutes");
            Assert.AreEqual(expected.Seconds, actual.Seconds, delta, "Seconds");
        }

        public static void AreEqual(Frustum expected, Frustum actual, float delta)
        {
	        AssertX.AreEqual(expected.Left, actual.Left, delta);
            AssertX.AreEqual(expected.Right, actual.Right, delta);
	        AssertX.AreEqual(expected.Top, actual.Top, delta);
	        AssertX.AreEqual(expected.Bottom, actual.Bottom, delta);
	        AssertX.AreEqual(expected.Near, actual.Near, delta);
	        AssertX.AreEqual(expected.Far, actual.Far, delta);
        }
    }
}
