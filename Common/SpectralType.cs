
namespace ConstellationStation.Common
{
    /// <summary>
    /// Module related to star spectral types.
    /// </summary>
    public static class Spectral
    {
        // Types
        /// <summary>
        /// Star spectral types.
        /// </summary>
        public enum SpectralType
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z
        }

        // Methods
        /// <summary>
        /// Returns a <see cref="SpectralType"/> by parsing <paramref name="spectral"/>.
        /// </summary>
        /// <param name="spectral">A string representing a spectral type.</param>
        /// <returns>A <see cref="SpectralType"/> by parsing <paramref name="spectral"/>.</returns>
        public static SpectralType Parse(string spectral)
        {
            SpectralType type;
            switch (spectral)
            {
                case "A":
                    type = SpectralType.A;
                    break;
                case "B":
                    type = SpectralType.B;
                    break;
                case "C":
                    type = SpectralType.C;
                    break;
                case "D":
                    type = SpectralType.D;
                    break;
                case "E":
                    type = SpectralType.E;
                    break;
                case "F":
                    type = SpectralType.F;
                    break;
                case "G":
                    type = SpectralType.G;
                    break;
                case "H":
                    type = SpectralType.H;
                    break;
                case "I":
                    type = SpectralType.I;
                    break;
                case "J":
                    type = SpectralType.J;
                    break;
                case "K":
                    type = SpectralType.K;
                    break;
                case "L":
                    type = SpectralType.L;
                    break;
                case "M":
                    type = SpectralType.M;
                    break;
                case "N":
                    type = SpectralType.N;
                    break;
                case "O":
                    type = SpectralType.O;
                    break;
                case "P":
                    type = SpectralType.P;
                    break;
                case "Q":
                    type = SpectralType.Q;
                    break;
                case "R":
                    type = SpectralType.R;
                    break;
                case "S":
                    type = SpectralType.S;
                    break;
                case "T":
                    type = SpectralType.T;
                    break;
                case "U":
                    type = SpectralType.U;
                    break;
                case "V":
                    type = SpectralType.V;
                    break;
                case "W":
                    type = SpectralType.W;
                    break;
                case "X":
                    type = SpectralType.X;
                    break;
                case "Y":
                    type = SpectralType.Y;
                    break;
                case "Z":
                    type = SpectralType.Z;
                    break;
                default:
                    type = SpectralType.A;
                    break;
            }
            return type;
        }
    }
}
