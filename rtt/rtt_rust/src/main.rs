#![allow(unused)]

use hex::ToHex;
use hmac_sha256::HMAC;
use openssl::base64;
use openssl::symm::{Cipher, Crypter, Mode};
use reqwest::Client;
use serde::Deserialize;
use serde::Serialize;
use std::time::Instant;
use std::time::{SystemTime, UNIX_EPOCH};

const ADDRESS: &str = "https://nlu.gree.com/api/t2c/prod/ap/query";
const CONTENT_TYPE: &str = "application/json;charset=UTF-8";
const KEY: &[u8] = b"df8daf7e2a81ded2";
const IV: &[u8] = b"df8daf7e2a81ded2";
const APP_KEY: &str = "3bf10e1a800051d";
const CIPHERTEXT: &str = r#"sXBQ8TfhlvBy+LLHfwBFvOAmgmKj2z3LSs+sD0rTuDFJJHfrlRP4G9QAtvB0SFAjDG3BbWF34JVmSnKJwFCFbDGeiNTp4NOq+NsC7l/1hxiiNt0gVsE+4XGfUryDF3EQqntSzg7SJsOHcbiecBPKio6z5yT7ru6xes8+ulvFH28="#;
const HEADER_SIZE: usize = 8;

const DATA_TEMP: &str = r#"{"device":{"macVoice":"48d890d762b0","macWifi":"48d890d762b0","mid":"10f03"},"query":"你好","user":{"hid":"","uid":""}}"#;

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct User {
    mid: String,
    uid: String,
}

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct Device {
    mac_wifi: String,
    mac_voice: String,
    mid: String,
}

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct DeviceLast {
    mac: String,
    mid: String,
}

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct Location {
    city: String,
    ip: String,
}

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct Data {
    user: User,
    device: Device,
    // device_last: DeviceLast,
    // location: Location,
    query: String,
}

#[derive(Serialize, Deserialize, Debug)]
#[serde(rename_all = "camelCase")]
struct DataJson {
    data: Data,
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Hello, world!");
    let mut data = data();
    // let data = data.replace("=", r#"\u003d\n"#);
    let auth = authorization(&data);
    println!("data==>>{};auth==>>{}", data, auth);
    let client = Client::new();
    let rep = client
        .post(ADDRESS)
        .header("Authorization", auth)
        .header("Content-Type", CONTENT_TYPE)
        .body(data)
        .send()
        .await?;
    println!("{:?}", rep);
    Ok(())
}

fn data() -> String {
    let data = Data {
        user: User {
            uid: String::new(),
            mid: String::new(),
        },
        device: Device {
            mac_voice: String::from("48d890d762b0"),
            mac_wifi: String::from("48d890d762b0"),
            mid: String::from("10f03"),
        },
        query: String::from("上一首"),
    };
    let data = serde_json::to_string(&data).unwrap();
    let data = convert_string_to_aes_128_cbc_base64(&data);
    let data = format!("{{\"data\":\"{}\"}}", data);
    println!("data:{}", data);
    data
}

fn authorization(data: &str) -> String {
    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs()
        .to_string();
    let content = format!("{}{}", data, now);
    println!("content:{}", content);
    let sign = HMAC::mac(content.as_bytes(), KEY);
    let sign = sign.encode_hex::<String>();
    let auth = format!("Appkey={},Timestamp={},Signature={}", APP_KEY, now, sign);
    auth
}

fn convert_string_to_aes_128_cbc_base64(src: &str) -> String {
    let mut encrypter = Crypter::new(Cipher::aes_128_cbc(), Mode::Encrypt, KEY, Some(IV)).unwrap();
    let block_size = Cipher::aes_128_cbc().block_size();
    let mut ciphertext = vec![0; src.len() + block_size];
    let mut count = encrypter.update(src.as_ref(), &mut ciphertext).unwrap();
    count += encrypter.finalize(&mut ciphertext[count..]).unwrap();
    ciphertext.truncate(count);
    base64::encode_block(&*ciphertext)
}

fn convert_base64_aes_128_cbc_to_string(src: &str) {
    // Create a cipher context for decryption.
    let source = base64::decode_block(src).unwrap();
    let mut decrypter = Crypter::new(Cipher::aes_128_cbc(), Mode::Decrypt, KEY, Some(IV)).unwrap();
    let block_size = Cipher::aes_128_cbc().block_size();
    let mut plaintext = vec![0; source.len() + block_size];
    // Decrypt 2 chunks of ciphertexts successively.
    let mut count = decrypter.update(&source, &mut plaintext).unwrap();
    count += decrypter.finalize(&mut plaintext[count..]).unwrap();
    plaintext.truncate(count);
    println!("{}", String::from_utf8_lossy(&*plaintext));
}

#[cfg(test)]
mod test {
    use super::User;

    #[test]
    fn test_user() {
        let user = User {
            mid: String::from("123456"),
            uid: String::from("123456789"),
        };
        let j = serde_json::to_string(&user).unwrap();
        println!("{}", j);
    }

    use super::Device;

    #[test]
    fn test_device() {
        let device = Device {
            mac_wifi: String::from("123456"),
            mac_voice: String::from("123455667"),
            mid: String::from("Ada2w24354"),
        };
        let j = serde_json::to_string(&device).unwrap();
        println!("{}", j);
    }

    use super::Location;

    #[test]
    fn test_location() {
        let location = Location {
            city: String::from("珠海"),
            ip: String::from("192.168.3.1"),
        };
        let j = serde_json::to_string(&location).unwrap();
        println!("{}", j);
    }

    use super::Data;
    use super::DeviceLast;

    #[test]
    fn test_all() {
        let data = Data {
            user: User {
                mid: String::from("123456"),
                uid: String::from("123456789"),
            },
            device: Device {
                mac_wifi: String::from("123456"),
                mac_voice: String::from("123455667"),
                mid: String::from("Ada2w24354"),
            },
            // device_last: DeviceLast {
            //     mac: String::new(),
            //     mid: String::new(),
            // },
            // location: Location {
            //     city: String::from("珠海"),
            //     ip: String::from("192.168.3.1"),
            // },
            query: String::from("珠海的天气"),
        };
        let j = serde_json::to_string(&data).unwrap();
        println!("{}", j);
    }
    use super::*;

    use std::time::Instant;
    use std::time::{SystemTime, UNIX_EPOCH};

    #[test]
    fn test_duration() {
        let now = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_secs();
        println!("{:?}", now);
    }

    #[test]
    fn test_hmac() {
        let auth_content = "HelloWorld!";
        let sign = HMAC::mac(auth_content.as_bytes(), KEY);
        let sign = sign.encode_hex::<String>();
        println!("{:?}", sign);
    }

    use super::*;
    #[test]
    fn test_base64() {
        convert_base64_aes_128_cbc_to_string(CIPHERTEXT);
    }

    #[test]
    fn test_auth() {
        let data = r#"{"data":"sXBQ8TfhlvBy+LLHfwBFvOAmgmKj2z3LSs+sD0rTuDFJJHfrlRP4G9QAtvB0SFAjDG3BbWF34JVm\nSnKJwFCFbDGeiNTp4NOq+NsC7l/1hxiiNt0gVsE+4XGfUryDF3EQqntSzg7SJsOHcbiecBPKio6z\n5yT7ru6xes8+ulvFH28\u003d\n"}1632376521"#;
        let sign = HMAC::mac(data.as_bytes(), KEY);
        let sign = sign.encode_hex::<String>();
        println!("{}", sign);
    }
}
