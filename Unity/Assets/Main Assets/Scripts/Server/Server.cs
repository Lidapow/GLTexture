using UnityEngine;
using System.Threading;
using PowIoC;

public abstract class Server : ScriptableObject, IServer {
	public RetrievedPacket retrievedPacket { get; set; }
	Thread thread;
	protected bool terminate;

	[Inject(false)]
	protected ILogger logger;

	void OnEnable () {
		terminate = false;
		thread = new Thread(new ThreadStart(OnExecute));
		thread.Start();
	}

	void OnDisable () {
		thread.Abort();
	}

	void OnExecute () {
		//Nap for inject
		Thread.Sleep(100);
		if(string.IsNullOrEmpty(logger.Context))
			logger.Context = this.GetType().ToString();
		Execute();
	}

	public void Stop () {
		terminate = true;
	}

	protected abstract void Execute ();
}