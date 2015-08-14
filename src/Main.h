class Main {
	public:
		static Main* INSTANCE ();

		void SetTexture (int textreID, int width, int height);
		void SetTexture (int textreID, int width, int height, int format);
		void DecodeVideo (int dataLen, char* data);
	private:
		Texture* m_Texture;
		Decoder* m_Decoder;
		Main* instance;
		Main ();
		~Main ();
}