using UnityEngine;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class ServerSocket : Server {

	protected override void Execute () {
		Socket server = null;

		IPEndPoint endPoint = new IPEndPoint(IPAddress.Loopback, 8080);
		server = new Socket(endPoint.AddressFamily, SocketType.Dgram, ProtocolType.Udp);

		server.Bind(endPoint);
		byte[] buffer = new byte[6 * 1024];
		int i = 0;
		for(;;){
			i = server.Receive(buffer);
			retrievedPacket(i, buffer);

			Thread.Sleep(3);
			if(terminate) break;
		}
		Debug.Log("Thread Stop");
	}
}