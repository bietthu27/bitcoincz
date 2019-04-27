## How to claim your BCZ coins

Below are 3 options to claim your BCZ coins.

> NOTE: KEEP YOUR PRIVATEKEYS SAFE!!! NEVER SHARE YOUR PRIVATEKEYS WITH
> ANYONE ELSE, IF YOU LOST YOUR PRIVATEKEYS WE CANNOT RECOVER YOUR
> COINS.

### How to claim your BCZ with your GXX or BZX privatekeys:

To reveal your walletaddress private key in your GXX, BZX desktop wallet:

Go to **_Help -> Debug Window -> Console_**.

if your wallet is encrypted (locked) then you need to decrypt it first:

    walletpassphrase “YOUR_PASSPHRASE/PASSWORD” 240

To reveal your walletaddress private key type:

    dumpprivkey “YOUR_WALLETADDRESS”

To import your walletaddress private key (GXX, BZX) in the BCZ desktop wallet:

Go to **_Tools -> Debug Console_**.

if your wallet is encrypted (locked) then you need to decrypt it first:

    walletpassphrase “YOUR_PASSPHRASE/PASSWORD” 240

To import your walletaddress private key type:

    importprivkey “YOUR_WALLETADDRESS_PRIVKEY”

The BCZ wallet will now automatically rescan and your BCZ will appear in your balance after it’s done.

## How to claim your BCZ with your GXX or BZX wallet.dat file:

Stop/quit the BCZ desktop wallet.

Copy paste the GXX or BZX wallet.dat file in your data application folder.

    -   Windows: C:\Users\Username\AppData\Roaming\BCZ
    -   Mac: ~/Users/Username/Library/Application Support/BCZ
    -   Unix: ~/.bcz

Restart the BCZ desktop wallet.

The BCZ wallet will now automatically rescan and your BCZ will appear in your balance after it’s done.

## How to claim your BCZ from a GXX or BZX dumpwallet file:

To export/dump your walletaddress private keys (GXX, BZX) at once in the your GXX, BZX desktop wallet:

Go to **_Help -> Debug Window -> Console_**.

if your wallet is encrypted (locked) then you need to decrypt it first:

    walletpassphrase “YOUR_PASSPHRASE/PASSWORD” 240

To export/dump the file :

    reveal_wallet_keys "YOUR_FILENAME"

The file will be saved in the data application folder. For Mac users in the rootfolder.

To import your walletaddress private keys (GXX, BZX) at once in the your GXX, BZX desktop wallet:

Go to **_Tools -> Debug Console_**.

if your wallet is encrypted (locked) then you need to decrypt it first:

    walletpassphrase “YOUR_PASSPHRASE/PASSWORD” 240

To import the file :

    importwallet "YOUR_FILENAME"

The BCZ wallet will now automatically rescan and your BCZ will appear in your balance after it’s done.
