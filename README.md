# High-Performance Multithreaded Web Server

A simple yet efficient HTTP 1.1 server implemented in modern C++. It uses non-blocking sockets and a thread pool to handle multiple simultaneous client connections and serve static files from a public directory.

## 🚀 Features

- HTTP 1.1 support (GET method)
- Serves static HTML files from a `public/` directory
- Non-blocking I/O using `poll()`
- Thread pool for handling concurrent client requests
- Modular C++ design with `Server`, `ThreadPool`, `Connection` classes
- Clean and minimal CMake-based build system

## 🧠 Skills Demonstrated

- Network programming (TCP, sockets)
- Multithreading with `std::thread`, `mutex`, and condition variables
- Low-level file and I/O handling
- Memory management and RAII in modern C++
- System-level debugging and performance tuning

## 📁 Project Structure

```
webserver/
├── include/            # Header files (declarations)
├── src/                # Source files (definitions)
├── public/             # Static files served over HTTP
├── main.cpp            # Entry point
├── CMakeLists.txt      # Build script
└── README.md
```

## 🔧 Build Instructions

1. Clone the repository:

```bash
git clone https://github.com/yourusername/High-Performance-Web-Server.git
cd High-Performance-Web-Server
```

2. Create and build the project:

```bash
mkdir build
cd build
cmake ..
make
```

## ▶️ Run the Server

Run the server from the **project root**:

```bash
./build/webserver
```

You should see:

```
Server running on port 8080
```

## 🌐 Access the Web Page

Open your browser and go to:

```
http://localhost:8080/
```

Or test using curl:

```bash
curl http://localhost:8080/
```

Make sure `public/index.html` exists:

```bash
mkdir -p public
echo "<h1>Hello, World!</h1>" > public/index.html
```

## 🛠 Future Enhancements

- Support for HTTP POST
- File MIME type detection
- Persistent connections (keep-alive)
- Basic rate limiting
- Logging module
- TLS (HTTPS) support

## 📄 License

This project is open-source and available under the MIT License.

## 🤝 Contributing

Pull requests are welcome! Feel free to fork this repository and submit improvements or bug fixes.
