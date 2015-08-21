using UnityEngine;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class ServerTcp : Server {

	protected override void Execute () {
		TcpListener server = null;
		NetworkStream stream = null;
		TcpClient client = null;

		server = new TcpListener(8080);
		server.Start();
		
		byte[] buffer = new byte[150 * 1024];
		int i = 0;

		for(;;){
			client = server.AcceptTcpClient();
			stream = client.GetStream();

			while ((i = stream.Read(buffer, 0, buffer.Length)) != 0){
				retrievedPacket(i, buffer);
				i = 0;

				if(terminate) break;
			}
			client.Close();
			Thread.Sleep(1000 / 30);
			if(terminate) break;
		}
		server.Stop();
		Debug.Log("Thread Stop");
	}
}