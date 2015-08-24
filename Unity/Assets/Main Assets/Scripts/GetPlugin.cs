using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using PowIoC;

public class GetPlugin : MonoBehaviour {
	[DllImport("GLTexture")]
	public extern static void SetTexture (int textureID, int width, int height, int format);
	[DllImport("GLTexture")]
	public extern static void DecodeVideo (int dataLen, byte[] data);
	[DllImport("GLTexture")]
	public extern static int Release ();

	public Texture2D tex;
	private bool tStop;
	private YieldInstruction wfeof;
	public string imageData;

	[Inject]
	IServer server;
	[Inject(false)]
	ILogger logger;

	void Awake () {
		Injector.Inject(this);
		logger.Context = this.GetType().ToString();
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
		wfeof = new WaitForEndOfFrame();
		StartCoroutine(CodecJobAsync());
	}



	IEnumerator CodecJobAsync () {
		while (!tStop) {
			yield return wfeof;
			GL.IssuePluginEvent(0);
		}
	}

	void CodecJob (int len, byte[] data) {
		DecodeVideo(len, data);
	}

	void OnDestroy () {
		logger.Log("Stop");
		tStop = true;
		server.Stop();
		Release();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
