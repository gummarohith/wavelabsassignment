using System;
using System.Collections.Generic;
using System.Timers;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace GraphsQuestions
{
    /// <summary>
    /// https://drive.google.com/file/d/16xZ0jWlknky825VYwMfK-1QmYt3cTbV6/view?usp=drivesdk

    /// </summary>
    [TestClass]
    public class NetworkDelayTimeTest
    {
        [TestMethod]
        public void ExampleTest()
        {
            int N = 4;
            int K = 2;
            int[][] times = { new[] { 2, 1, 1 }, new[] { 2, 3, 1 }, new[] { 3, 4, 1 } };
            NetWorkDelayTimeDfs dfs = new NetWorkDelayTimeDfs();
            Assert.AreEqual(2, dfs.NetworkDelayTime(times, N, K));
        }
    }

    public class NetWorkDelayTimeDfs
    {
        private Dictionary<int, int> dist;

        public int NetworkDelayTime(int[][] times, int N, int K)
        {
            var graph = new Dictionary<int, List<List<int>>>();
            // build a dictionary
            // key = from vertex
            // values - weight and destination
            foreach (var edge in times)
            {
                if (!graph.TryGetValue(edge[0], out var temp))
                {
                    temp = graph[edge[0]] = new List<List<int>>();
                }

                temp.Add(new List<int> {edge[2], edge[1]});
            }

            // sort by the weight
            foreach (var node in graph)
            {
                node.Value.Sort((a, b) => a[0] - b[0]);
            }

            // all the edges get max value
            dist = new Dictionary<int, int>();
            for (int i = 1; i <= N; i++)
            {
                dist.Add(i, int.MaxValue);
            }

            DFS(graph, K, 0);

            //  compute the max distance.
            // if one of the edges equals int.max
            // we can't reach it so we return -1;
            int ans = 0;
            foreach (var cand in dist.Values)
            {
                if (cand == int.MaxValue)
                {
                    return -1;
                }

                ans = Math.Max(ans, cand);
            }

            return ans;
        }

        private void DFS(Dictionary<int, List<List<int>>> graph, int node, int elapsed)
        {
            //if the distance bigger then what we already have for this node.
            // return there is nothing to update
            if (elapsed >= dist[node])
            {
                return;
            }

            dist[node] = elapsed;
            if (graph.ContainsKey(node))
            {
                //we run DFS to all the other nodes
                //we update the total distance to elapsed + weight
                foreach (var info in graph[node])
                {
                    DFS(graph, info[1], elapsed + info[0]);
                }
            }
        }
    }

