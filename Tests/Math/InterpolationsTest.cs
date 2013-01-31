using System;
using NUnit.Framework;

namespace ConstellationStation.Math
{
    [TestFixture]
    public class InterpolationsTest
    {
        private const float DELTA = 0.001f;

        [Test]
        public void LerpTestValue1()
        {
            Assert.AreEqual(3.0f, Interpolations.Lerp(0.0f, 3.0f, 5.0f), DELTA);
        }

        [Test]
        public void LerpTestValue2()
        {
            Assert.AreEqual(5.0f, Interpolations.Lerp(1.0f, 3.0f, 5.0f), DELTA);
        }

        [Test]
        public void LerpTestMiddle()
        {
            Assert.AreEqual(4.0f, Interpolations.Lerp(0.5f, 3.0f, 5.0f), DELTA);
        }

        [Test]
        public void LerpTestValue1Greater()
        {
            Assert.AreEqual(4.0f, Interpolations.Lerp(0.5f, 5.0f, 3.0f), DELTA);
        }

        [Test]
        public void LerpTestValue1Value2Equal()
        {
            Assert.AreEqual(4.0f, Interpolations.Lerp(0.0f, 4.0f, 4.0f), DELTA);
        }

        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void LerpTestRatioTooSmall()
        {
            Interpolations.Lerp(-0.1f, 0.0f, 0.0f);
        }

        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void LerpTestRatioTooLarge()
        {
            Interpolations.Lerp(1.1f, 0.0f, 0.0f);
        }
    }
}
