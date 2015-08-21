using UnityEngine;
using System.Threading;

public abstract class Server : ScriptableObject, IServer {
	public RetrievedPacket retrievedPacket { get; set; }
	Thread thread;
	protected bool terminate;

	void OnEnable () {
		terminate = false;
		thread = new Thread(new ThreadStart(Execute));
		thread.Start();
	}

	public void Stop () {
		terminate = true;
	}

	protected abstract void Execute ();
}