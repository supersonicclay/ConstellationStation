using NUnit.Framework;

namespace ConstellationStation.Data
{
    [TestFixture]
    public class NavigationTests
    {
        private const float DELTA = 0.01f;

        [Test]
        public void TestXRotationOptimal()
        {
            Navigation navigation = new Navigation();
            navigation.XRotation = 0.5f;
            Assert.AreEqual(0.5f, navigation.XRotation, DELTA);
        }

        [Test]
        public void TestXRotationTooLarge()
        {
            Navigation navigation = new Navigation();
            navigation.XRotation = 2.0f;
            Assert.AreEqual(System.Math.PI / 2, navigation.XRotation, DELTA);
        }

        [Test]
        public void TestXRotationTooSmall()
        {
            Navigation navigation = new Navigation();
            navigation.XRotation = -2.0f;
            Assert.AreEqual(-System.Math.PI / 2, navigation.XRotation, DELTA);
        }

        [Test]
        public void TestYRotationOptimal()
        {
            Navigation navigation = new Navigation();
            navigation.YRotation = 0.5f;
            Assert.AreEqual(0.5f, navigation.YRotation, DELTA);
        }

        [Test]
        public void TestYRotationTooSmall()
        {
            Navigation navigation = new Navigation();
            navigation.YRotation = -0.1f;
            Assert.AreEqual(-0.1f + (System.Math.PI * 2), navigation.YRotation, DELTA);
        }

        [Test]
        public void TestYRotationTooLarge()
        {
            Navigation navigation = new Navigation();
            navigation.YRotation = 7.0f;
            Assert.AreEqual(7.0f - (System.Math.PI * 2), navigation.YRotation, DELTA);
        }

        [Test]
        public void TestYRotationWayTooLarge()
        {
            Navigation navigation = new Navigation();
            navigation.YRotation = 15.0f;
            Assert.AreEqual(15.0f - (2 * System.Math.PI * 2), navigation.YRotation, DELTA);
        }

        [Test]
        public void TestZoomOptimal()
        {
            Navigation navigation = new Navigation();
            navigation.Zoom = 0.5f;
            Assert.AreEqual(0.5f, navigation.Zoom, DELTA);
        }

        [Test]
        public void TestZoomTooSmall()
        {
            Navigation navigation = new Navigation();
            navigation.Zoom = -0.1f;
            Assert.AreEqual(0.0f, navigation.Zoom, DELTA);
        }

        [Test]
        public void TestZoomTooLarge()
        {
            Navigation navigation = new Navigation();
            navigation.Zoom = 1.1f;
            Assert.AreEqual(1.0f, navigation.Zoom, DELTA);
        }
    }
}
