﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SimpleParallelism
{
    public class Program
    {
        public static void TaskExample()
        {
            var t = Task.Run(() =>
            {
                Thread.Sleep(4000); // Wait for 4 seconds
                Console.WriteLine("Good morning!");
            });

            Thread.Yield(); // Give control to OS to run other tasks

            Console.WriteLine("Hello world! I am doing asynchronous work here");

            // We need to wait, here, otherwise program might exit!
            t.Wait();

            Console.WriteLine("Joined thread. Now, we can exit!");
        }
                
        public static void ListExample()
        {
            var list = new List<int>();
            for (int i = 0; i < 1000; i++)
                list.Add(i);

            int count = 0;
            object countLck = new object();
            
            // Object to box counter
            BoxedInt countObj = new BoxedInt
            {
                Counter = 0
            };

            Parallel.ForEach(list, (item) =>
            {
                Console.WriteLine($"I am working on item {item}");

                // Atomically increment count....
                Interlocked.Increment(ref count);
                
                // .. or do it with locks, to isolate a critical section
                lock (countLck) // An object is required here.
                {
                    count++;
                }

                // Typically, you lock the entire object, if possible
                // we previously used 'count', which is _not_ an object
                lock (countObj)
                {
                    countObj.Counter++;
                }
            });

            Console.WriteLine($"count now is {count}");
            Console.WriteLine($"countObj.Count now is {countObj.Counter}");
        }

        public static void ArrayExample()
        {
            const int size = 4;
            int []A = new int[size];

            for(int i=0; i<size; i++)
                A[i] = i;

            for (int i = 0; i < size; i++)
                Console.WriteLine($"A[{i}] is {A[i]}");

            Parallel.ForEach(A, (item) =>
            {
                item *= 2;
                Console.WriteLine($"item now is {item}");
            });

            for (int i = 0; i < size; i++)
                Console.WriteLine($"A[{i}] is {A[i]}");

            var boxedList = BoxedInt.CreateList(A);
            Parallel.ForEach(boxedList, (item) =>
            {
                item.Counter *= 2;
            });

            foreach (var i in boxedList)
                Console.WriteLine(i);

        }

        public static void RunAction(Action action)
        {
            action();
        }

        public static void LambdaExample()
        {
            Action printHelloWorldLambda = () => Console.WriteLine("Hello World! I am a lambda function!");

            printHelloWorldLambda();

            Action anotherAction = printHelloWorldLambda;

            RunAction(printHelloWorldLambda);

            RunAction(anotherAction);

            RunAction(() =>
            {
                Console.WriteLine("Hello World! I am a lambda fuction, " +
                    "inlined in the 'RunAction' function call!");
            });

        }

        static void ClosureExample()
        {
            const int size = 10;
            int[] A = new int[size];

            for (int i = 0; i < size; i++)
                A[i] = i;

            foreach (var i in A)
            {
                Task.Run(() =>
                {
                    Thread.Sleep(1000);
                    Console.WriteLine(i.ToString());
                });
            }
        }

        static void Main(string[] args)
        {
            //ClosureExample();
            //TaskExample();
            //ListExample();
            ArrayExample();
            //LambdaExample();
            Console.ReadLine();
            return;
        }
    }
}
