/*
 * Copyright (C) 2012 Webdoc SA
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Sankoré.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "UBCryptoUtils.h"

#include <openssl/aes.h>

#include "core/memcheck.h"

UBCryptoUtils* UBCryptoUtils::sInstance(0);
QString UBCryptoUtils::sAESKey("9ecHaspud9uD9ste5erAchehefrup3echej-caje6&thestawacuk=h#F3jet3aF");
QString UBCryptoUtils::sAESSalt("6f0083e0-a90c-11de-ac21-0002a5d5c51b");

UBCryptoUtils* UBCryptoUtils::instance()
{
    if(!sInstance)
        sInstance = new UBCryptoUtils(UBApplication::staticMemoryCleaner);

    return sInstance;
}

void UBCryptoUtils::destroy()
{
    if (sInstance)
        delete sInstance;
    sInstance = NULL;
}


UBCryptoUtils::UBCryptoUtils(QObject * pParent)
    : QObject(pParent)
{
    aesInit();
}


UBCryptoUtils::~UBCryptoUtils()
{
    // TODO UB 4.x aes destroy
}


QString UBCryptoUtils::symetricEncrypt(const QString& clear)
{
    QByteArray clearData = clear.toUtf8();

    int cipheredLength = clearData.length() + AES_BLOCK_SIZE;
    int paddingLength = 0;
    unsigned char *ciphertext = (unsigned char *)malloc(cipheredLength);

    if(!EVP_EncryptInit_ex(&mAesEncryptContext, NULL, NULL, NULL, NULL))
        return QString();

    if(!EVP_EncryptUpdate(&mAesEncryptContext, ciphertext, &cipheredLength, (unsigned char *)clearData.data(), clearData.length()))
        return QString();

    /* update ciphertext with the final remaining bytes */
    if(!EVP_EncryptFinal_ex(&mAesEncryptContext, ciphertext + cipheredLength, &paddingLength))
        return QString();

    QByteArray cipheredData((const char *)ciphertext, cipheredLength + paddingLength);

    free(ciphertext);

    return QString::fromAscii(cipheredData.toBase64());
}


QString UBCryptoUtils::symetricDecrypt(const QString& encrypted)
{
    QByteArray encryptedData = QByteArray::fromBase64(encrypted.toAscii());

    int encryptedLength = encryptedData.length();
    int paddingLength = 0;
    unsigned char *plaintext = (unsigned char *)malloc(encryptedLength);

    if(!EVP_DecryptInit_ex(&mAesDecryptContext, NULL, NULL, NULL, NULL))
        return QString();

    if(!EVP_DecryptUpdate(&mAesDecryptContext, plaintext, &encryptedLength, (const unsigned char *)encryptedData.data(), encryptedData.length()))
        return QString();

    if(!EVP_DecryptFinal_ex(&mAesDecryptContext, plaintext + encryptedLength, &paddingLength))
        return QString();

    int len = encryptedLength + paddingLength;
    QByteArray clearData((const char *)plaintext, len);

    free(plaintext);

    return QString::fromUtf8(clearData);;
}


void UBCryptoUtils::aesInit()
{
    int i, nrounds = 5;
    unsigned char key[32], iv[32];
    unsigned char *key_data = (unsigned char *)sAESKey.toAscii().data();
    int key_data_len = sAESKey.length();

    i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (unsigned char *)sAESSalt.toAscii().data(), key_data,
            key_data_len, nrounds, key, iv);

    if (i != 32)
    {
        qWarning() << QString("Key size is %1 bits - should be 256 bits").arg(i);
        return;
    }

    EVP_CIPHER_CTX_init(&mAesEncryptContext);
    EVP_EncryptInit_ex(&mAesEncryptContext, EVP_aes_256_cbc(), NULL, key, iv);
    EVP_CIPHER_CTX_init(&mAesDecryptContext);
    EVP_DecryptInit_ex(&mAesDecryptContext, EVP_aes_256_cbc(), NULL, key, iv);
}
