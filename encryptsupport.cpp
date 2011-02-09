/*
 *  Copyright (c) 2010 Kaushal M <kshlmster@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "encryptsupport.h"
#include "passphrasedialog.h"

#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCryptographicHash>
#include <QFile>
#include <QMessageBox>
#include <QMaemo5InformationBox>

#include  <openssl/evp.h>

encryptSupport::encryptSupport(QWidget *parent):
        QWidget(parent)
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, "/tmp/");
    getDetails();
}

void encryptSupport::getDetails()
{
    QSettings passphraseConf("freoffice", "plugin-settings");
    passphraseConf.beginGroup("encrypt-support");
    QSettings passphraseTemp(QSettings::SystemScope, "freoffice-encryption-support-temp");
    if (!passphraseTemp.contains("key")) {
        enterPassphraseDialog();
        return;
    }
    key = passphraseTemp.value("key").toByteArray();
    iv = passphraseConf.value("iv").toByteArray();
}

void encryptSupport::enterPassphraseDialog()
{
    QSettings passphraseConf("freoffice", "plugin-settings");
    passphraseConf.beginGroup("encrypt-support");
    if(!passphraseConf.contains("hash")) {
        newPassphraseDialog();
        return;
    }
    QString hash = passphraseConf.value("hash").toString();
    QString passphrase;
    while(true) {
        int val = 0;
        passphrase = passphraseDialog::getPassphrase(val, this);
        if(val == 1) {
            QMaemo5InformationBox::information(this,"All saved details will be lost", QMaemo5InformationBox::NoTimeout);
            deleteSettings();
            newPassphraseDialog();
            return;
        }
        else if (val == 0) {
            if(QCryptographicHash::hash(passphrase.toUtf8(), QCryptographicHash::Sha1).toHex() == hash.toUtf8()) {
                break;
            }
            else {
                QMaemo5InformationBox::information(this, "Wrong passphrase.\nEnter again.", QMaemo5InformationBox::NoTimeout);
            }
        }
        else if (val == -1) {
            emit cancelled();
            return;
        }
    }
    QSettings passphraseTemp(QSettings::SystemScope, "freoffice-encryption-support-temp");
    passphraseTemp.setValue("key", passphrase);
    passphraseTemp.sync();
    getDetails();
}

void encryptSupport::deleteSettings() {
    QSettings passphraseConf("freoffice", "plugin-settings");
    passphraseConf.clear();
    passphraseConf.sync();

    QSettings passphraseTemp(QSettings::SystemScope, "freoffice-encryption-support-temp");
    passphraseTemp.clear();
    passphraseTemp.sync();
}

void encryptSupport::newPassphraseDialog()
{
    QString passphrase;
    while("" == passphrase) {
        passphrase = QInputDialog::getText(this,"New Passphrase", "Please enter a phrase which is long.\nThis phrase will be used to encrypt your passwords", QLineEdit::Normal,"");
    }
    QSettings passphraseConf("freoffice","plugin-settings");
    passphraseConf.beginGroup("encrypt-support");
    QString hash(QCryptographicHash::hash(passphrase.toUtf8(), QCryptographicHash::Sha1).toHex());
    passphraseConf.setValue("hash",hash);
    QFile f("/dev/urandom");
    f.open(QFile::ReadOnly);
    QByteArray ivInit = f.read(8);
    f.close();
    passphraseConf.setValue("iv", ivInit);
    passphraseConf.sync();
    QSettings passphraseTemp(QSettings::SystemScope,"freoffice-encryption-support-temp");
    passphraseTemp.setValue("key", passphrase);
    passphraseTemp.sync();
    getDetails();
}

QString encryptSupport::encrypt(const QString & dataString)
{
    QByteArray data = dataString.toUtf8();
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    EVP_EncryptInit(&ctx, EVP_bf_cbc(), (unsigned char*)key.constData(), (unsigned char*)iv.constData());
    unsigned char outbuf[1024];
    int len = data.length();
    int outlen, tmplen;
    EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)data.constData(), len);
    EVP_EncryptFinal_ex(&ctx, outbuf+len, &tmplen);
    outlen += tmplen;
    EVP_CIPHER_CTX_cleanup(&ctx);
    QByteArray encData((const char*)outbuf, outlen);
    return QString(encData.toHex());
}

QString encryptSupport::decrypt(const QString &dataString)
{
    QByteArray data = QByteArray::fromHex(dataString.toUtf8());
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    EVP_DecryptInit(&ctx, EVP_bf_cbc(), (unsigned char*)key.constData(), (unsigned char*)iv.constData());
    unsigned char outbuf[1024];
    int len = data.length();
    int outlen, tmplen;
    EVP_DecryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)data.constData(), len);
    EVP_DecryptFinal(&ctx, outbuf+outlen, &tmplen);
    EVP_CIPHER_CTX_cleanup(&ctx);
    QByteArray decData((const char*)outbuf, outlen);
    return QString(decData);
}
