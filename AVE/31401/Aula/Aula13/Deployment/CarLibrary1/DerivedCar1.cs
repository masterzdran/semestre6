using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CarLibrary1
{
   
        public class SportsCar : Car1
        {
            public SportsCar() { }
            public SportsCar(string name, int maxSp, int currSp)
                : base(name, maxSp, currSp) { }

            public override void TurboBoost()
            {
                MessageBox.Show("Ramming speed!", "Faster is better...");
            }

            public void TurnOnRadio(bool turnOn, int volumn)
            {
                MessageBox.Show("Cranking tunes!");
            }
        }

        public class MiniVan : Car1
        {
            public MiniVan() { }
            public MiniVan(string name, int maxSp, int currSp)
                : base(name, maxSp, currSp) { }

            public override void TurboBoost()
            {
                // Minivans have poor turbo capabilities!
                egnState = EngineState.engineDead;
                MessageBox.Show("Eek!", "Your engine block exploded!");
            }
        }
    }

