using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;

namespace AsyncWebApp.Controllers
{
    /// <summary>
    /// This class is the application Controller. Both metods/web endpoints
    /// fetch a webpage from a url, and return the webpage content to the caller
    /// </summary>
    [RoutePrefix("api")]
    public class EndpointController : ApiController
    {
        static string MyUrl = "http://google.com";

        /// <summary>
        /// Endpoint that runs synchronously
        /// </summary>
        /// <returns></returns>
        [Route("test/sync")]
        [HttpGet]
        public IHttpActionResult SyncEndpoint()
        {
            var ret = AsyncTasks.Program.GetHtmlWithTask(MyUrl);
            // ret is a Task, and this code is synchronous, because we do not use await
            return Ok(ret.Result);
        }

        [Route("test/async")]
        [HttpGet]
        public async Task<IHttpActionResult> AsyncEndpoint()
        {
            var ret = await AsyncTasks.Program.AsyncCallWrapper(MyUrl);
            // ret is a Task, and this code is asynchronous, because we use async/await
            return Ok(ret);
        }

    }
}
