public delegate void RetrievedPacket (int len, byte[] data);

public interface IServer {
	RetrievedPacket retrievedPacket { get; set; }
	void Stop ();
}