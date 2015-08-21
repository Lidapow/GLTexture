using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System.Threading;
using PowIoC;

public class GetPlugin : MonoBehaviour {
	[DllImport("GLTexture")]
	public extern static void SetTexture (int textureID, int width, int height, int format);
	[DllImport("GLTexture")]
	public extern static void DecodeVideo (int dataLen, byte[] data);
	[DllImport("GLTexture")]
	public extern static int Release ();

	public Texture2D tex;
	private Thread thread;
	private bool tStop;
	private YieldInstruction wfeof;
	public string imageData;

	[Inject]
	IServer server;

	void Awake () {
		Injector.Inject(this);
		server.retrievedPacket += CodecJob;
	}

	// Use this for initialization
	void Start () {
		tex = new Texture2D(640, 480, TextureFormat.RGB24, false);
		tex.wrapMode = TextureWrapMode.Clamp;
		renderer.sharedMaterial.mainTexture = tex;

		SetTexture(
			tex.GetNativeTextureID(),
			tex.width,
			tex.height,
			0
		);

		tStop = false;
		// thread = new Thread(new ThreadStart(CodecJob));
		// thread.Start();
		wfeof = new WaitForEndOfFrame();
		StartCoroutine(CodecJobAsync());
	}



	IEnumerator CodecJobAsync () {
		while (!tStop) {
			// yield return wfeof;
			yield return 0;
			GL.IssuePluginEvent(0);
			// DecodeVideo(0, "t");
		}
	}

	void CodecJob (int len, byte[] data) {
		DecodeVideo(len, data);
	}

	void OnDestroy () {
		Debug.Log("Stop");
		tStop = true;
		server.Stop();
		Release();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
