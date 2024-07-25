							
								HƯỚNG DẪN CÀI ĐẶT ĐỒ HỌA TRÊN DEV C++ CÁC PHIÊN BẢN MỚI
											  "Tạm biệt Dev C++ 4.9.9.2"
								  
	Mình đã test thành công, các bạn chú ý đọc kĩ hướng dẫn.
	

- Đường dẫn (Path):
	+ Với Windows 32 bit:
		Path="C:\Program Files\Dev-Cpp"
	+ Với Windows 64 bit:
		Path="C:\Program Files (x86)\Dev-Cpp"
- Hướng dẫn cài đặt:
	+ Đối với Dev C++ 32 bit:
		Bước 1: Copy 2 file "graphics.h" và "winbgim.h" vào thư mục "(Path)\MinGV32\include".
		Bước 2: Copy file "libbgi.a" vào thư mục "(Path)\MinGV32\lib".
		Bước 3:	Copy 2 file "6-ConsoleAppGraphics.template" và "ConsoleApp_cpp_graph.txt" vào thư mục "(Path)\Templates".
	+ Đối với Dev C++ 64 bit:
		Bước 1: Copy 2 file "graphics.h" và "winbgim.h" vào thư mục "(Path)\MinGW64\x86_64-w64-mingw32\include".
		Bước 2: Copy file "libbgi.a" vào thư mục "(Path)\MinGW64\x86_64-w64-mingw32\lib".
		Bước 3:	Copy 2 file "6-ConsoleAppGraphics.template" và "ConsoleApp_cpp_graph.txt" vào thư mục "(Path)\Templates".
- Hướng dẫn sử dụng: Sau khi cài đặt theo các bước như hướng dẫn ở trên, các bạn mở Dev C++ lên.
	Bước 1: Nếu bạn cài Dev C++ 32 bit thì bỏ qua bước này, còn nếu là 64 bit thì các bạn chọn trình biên dịch là
			TDM-GCC 32 bit ứng với phiên bản Dev C++ bạn cài đặt (Đây là bước bắt buộc và phải làm từ đầu, nếu không
			thì sẽ không chạy được đồ họa).
			Ví dụ: Nếu Dev C++ 5.6.3 64 bit thì bạn sẽ chọn trình biên dịch là "TDM-GCC 4.8.1 32 bit Release".
	Bước 2: Tạo một Project mới bằng cách chọn File -> New -> Project...
			+ Chọn Console Graphics Application.
			+ Tick vào ô C++ Project.
			+ Gõ tên Project vào ô Name.
			+ Click Ok và chọn vị trí lưu.
	Bước 3: Tiến hành lập trình đồ họa và chạy thử thôi (Các bạn có thế sử dụng hai project được chuẩn bị sẵn để test).
	
*** Chú ý: Khi sử dụng chỉ có thể gọi một trong hai thư viện.