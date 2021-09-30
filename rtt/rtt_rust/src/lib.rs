#![no_std]

use rtt_rs::*;
use rtt_rs::thread::Thread;
use alloc::string::{String, ToString};
use hmac_sha256::HMAC;
use data_encoding::BASE64;
use libaes::Cipher;
use serde::{Serialize, Deserialize};

entry!(main);
fn main() {
    println!("Hello world! from rust");
    // let th = Thread::new();
    // th.start(|| {
    //     let mut count = 0;
    //     loop {
    //         println!("{},count=>{}", "Hello from rust", count);
    //         count += 1;
    //         Thread::delay(50);
    //     }
    // }).unwrap();
    let mut b = String::from("Hello World!");
    let mut hello = BASE64.encode(b.as_bytes());
    println!("base64:{}", hello);
    let mac = HMAC::mac(hello.as_bytes(), b"1234567890abcdef");
    let mac_hex = hex::encode(mac);
    println!("mac_hex:{}", mac_hex);


    let my_key = b"1234567890abcdef"; // key is 16 bytes, i.e. 128-bit
    let plaintext = b"HelloWorld!";
    let iv = b"1234567890abcdef";
    let cipher = Cipher::new_128(my_key);
    let encrypted = cipher.cbc_encrypt(iv, plaintext);
    let encrypted = BASE64.encode(&encrypted);
    println!("encrypted:{}", encrypted);
    let user = User {
        name: String::from("张三"),
        age: 16,
    };
    let json = serde_json_core::to_string::<User, 120>(&user).unwrap().to_string();
    println!("json:{}", json);
}

#[derive(Serialize, Deserialize)]
struct User {
    name: String,
    age: u8,
}

