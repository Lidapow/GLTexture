using UnityEngine;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class ServerUdp : Server {

	protected override void Execute () {
		UdpClient server = null;

		server = new UdpClient(8080) { DontFragment = true };
		IPEndPoint endPoint = new IPEndPoint(IPAddress.Loopback, 8080);
		for(;;){
			byte[] receive = server.Receive(ref endPoint);
			retrievedPacket(receive.Length, receive);

			if(terminate) break;
		}

		logger.Log("Thread Stop");
	}
}