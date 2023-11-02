use actix_web::{App, HttpServer, HttpRequest, Result, web};
use actix_web::middleware::DefaultHeaders;
use actix_files::Files;

async fn index(request: HttpRequest) -> Result<actix_files::NamedFile> {
    if let Some(client_address) = request.peer_addr() {
        println!("Client connected: {}", client_address.ip());
    } else {
        println!("Client connected (address unknown)");
    }

    Ok(actix_files::NamedFile::open("www/index.html")?)
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    println!("Server running...");
    HttpServer::new(|| {
        App::new()
            .wrap(
                DefaultHeaders::new()
                    .add(("Referrer-Policy", "no-referrer")))
            .route("/", web::get().to(index))
            .service(Files::new("/www", "./www").prefer_utf8(true))
    })
    .bind("0.0.0.0:8080")?
    .run()
    .await
}
