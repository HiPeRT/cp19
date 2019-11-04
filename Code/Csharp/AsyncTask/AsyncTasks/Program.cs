using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace AsyncTasks
{
    public class Program
    {
        // We want to fetch this url. Http calls are the typical work that can be done asynchronously
        static readonly string Url = "https://www.dotnetfoundation.org";

        /// <summary>
        /// This function shows how to use Tasks to execute background work
        /// This function is _asynchronous_ because we use the async/await constructs
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        public static async Task<string> GetHtmlWithAsyncAwait(string url)
        {
            // Execution is synchronous here
            var client = new HttpClient();
            var t = await client.GetStringAsync(url);

            // Now, the async part begins.
            // This code is executed when client.GetStringAsync populates t.Result,
            // because I used the async/await keywords
            // Task<string> t is a _promise_

            Console.WriteLine("[GetHtmlWithAsyncAwait] I am doing something here..");
            Console.WriteLine("[GetHtmlWithAsyncAwait] I am doing something else..");

            return t;
        }

        /// <summary>
        /// This function shows how to use Tasks to execute background work
        /// This function is _synchronous_
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        public static Task<string> GetHtmlWithTask(string url)
        {
            // Execution is synchronous here
            var client = new HttpClient();
            Task<string> t = client.GetStringAsync(url);

            // This is synchronous
            // This code is executed immediately, and it returns a Task<string>
            // which will do the work in background for us

            Console.WriteLine("[GetHtmlWithTask] I am doing something here..");
            Console.WriteLine("[GetHtmlWithTask] I am doing something else..");

            return t;
        }

        /// <summary>
        /// This function shows how to create a "chain" of nested async/await
        /// functions, so to "propagate" asyncronicity code in bigger programs
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        public static async Task<string> AsyncCallWrapper(string url)
        {
            var r = await GetHtmlWithAsyncAwait(url); // r is a string
            //var r = GetHtmlWithAsyncAwait(url); // r is a Task
            //var r = GetHtmlWithTask(url); // r is a Task

            // ascync code (as we use await here above)
            Console.WriteLine("[Foo] I am doing something here..");
            Console.WriteLine("[Foo] I am doing something else..");

            return r;
        }

        /// <summary>
        /// Every game has to end: this cannot be marked async!
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            //var r = await AsyncCallWrapper(); // This is not legal
            var r = AsyncCallWrapper(Url);
            //var r = GetHtmlWithTask(Url);

            Console.WriteLine("[Main]  I am doing something asynchronously, here");

            Console.WriteLine("[Main] I can do everything I want here :)! As soon as I don't touch r.Result..");

            Console.WriteLine($"[Main] r is {r.Result}");

            Console.WriteLine("[Main] After reading result");

            Console.ReadLine();
        }
    }
}
