using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleParallelism
{
    public class BoxedInt
    {
        public int Counter;

        public static IList<BoxedInt> CreateList(int[] array)
        {
            var ret = new List<BoxedInt>();

            foreach (var a in array)
                ret.Add(new BoxedInt() { Counter = a });
            return ret;
        }

        public override string ToString()
        {
            return Counter.ToString();
        }
    }
}
