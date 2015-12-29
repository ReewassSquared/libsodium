
#define TEST_NAME "pwhash_argon2i"
#include "cmptest.h"

#define OUT_LEN 128
#define OPSLIMIT 2
#define MEMLIMIT 10000000

static void tv(void)
{
    static struct {
        const char         *passwd_hex;
        size_t              passwdlen;
        const char         *salt_hex;
        size_t              outlen;
        unsigned long long  opslimit;
        size_t              memlimit;
        unsigned int        lanes;
    } tests[] = {
          { "a347ae92bce9f80f6f595a4480fc9c2fe7e7d7148d371e9487d75f5c23008ffae0"
            "65577a928febd9b1973a5a95073acdbeb6a030cfc0d79caa2dc5cd011cef02c08d"
            "a232d76d52dfbca38ca8dcbd665b17d1665f7cf5fe59772ec909733b24de97d6f5"
            "8d220b20c60d7c07ec1fd93c52c31020300c6c1facd77937a597c7a6",
            127,
            "5541fbc995d5c197ba290346d2c559dedf405cf97e5f95482143202f9e74f5c2",
            155, 6, 7256678, 1 },
          { "e125cee61c8cb7778d9e5ad0a6f5d978ce9f84de213a8556d9ffe202020ab4a6ed"
            "9074a4eb3416f9b168f137510f3a30b70b96cbfa219ff99f6c6eaffb15c06b60e0"
            "0cc2890277f0fd3c622115772f7048adaebed86e",
            86,
            "f1192dd5dc2368b9cd421338b22433455ee0a3699f9379a08b9650ea2c126f0d",
            250, 8, 7849083, 1 },
          { "92263cbf6ac376499f68a4289d3bb59e5a22335eba63a32e6410249155b956b6a3"
            "b48d4a44906b18b897127300b375b8f834f1ceffc70880a885f47c33876717e392"
            "be57f7da3ae58da4fd1f43daa7e44bb82d3717af4319349c24cd31e46d295856b0"
            "441b6b289992a11ced1cc3bf3011604590244a3eb737ff221129215e4e4347f491"
            "5d41292b5173d196eb9add693be5319fdadc242906178bb6c0286c9b6ca6012746"
            "711f58c8c392016b2fdfc09c64f0f6b6ab7b",
            183,
            "3b840e20e9555e9fb031c4ba1f1747ce25cc1d0ff664be676b9b4a90641ff194",
            249, 7, 7994791, 1 },
          { "027b6d8e8c8c474e9b69c7d9ed4f9971e8e1ce2f6ba95048414c3970f0f09b70e3"
            "b6c5ae05872b3d8678705b7d381829c351a5a9c88c233569b35d6b0b809df44b64"
            "51a9c273f1150e2ef8a0b5437eb701e373474cd44b97ef0248ebce2ca0400e1b53"
            "f3d86221eca3f18eb45b702b9172440f774a82cbf1f6f525df30a6e293c873cce6"
            "9bb078ed1f0d31e7f9b8062409f37f19f8550aae",
            152,
            "eb2a3056a09ad2d7d7f975bcd707598f24cd32518cde3069f2e403b34bfee8a5",
            5, 4, 1397645, 1 },
          { "4a857e2ee8aa9b6056f2424e84d24a72473378906ee04a46cb05311502d5250b82"
            "ad86b83c8f20a23dbb74f6da60b0b6ecffd67134d45946ac8ebfb3064294bc097d"
            "43ced68642bfb8bbbdd0f50b30118f5e",
            82,
            "39d82eef32010b8b79cc5ba88ed539fbaba741100f2edbeca7cc171ffeabf258",
            190, 1, 5432947, 1 },
          { "1845e375479537e9dd4f4486d5c91ac72775d66605eeb11a787b78a7745f1fd005"
            "2d526c67235dbae1b2a4d575a74cb551c8e9096c593a497aee74ba3047d911358e"
            "de57bc27c9ea1829824348daaab606217cc931dcb6627787bd6e4e5854f0e8",
            97,
            "3ee91a805aa62cfbe8dce29a2d9a44373a5006f4a4ce24022aca9cecb29d1473",
            212, 7, 13101817, 1 },
          { "c7b09aec680e7b42fedd7fc792e78b2f6c1bea8f4a884320b648f81e8cf515e8ba"
            "9dcfb11d43c4aae114c1734aa69ca82d44998365db9c93744fa28b63fd16000e82"
            "61cbbe083e7e2da1e5f696bde0834fe53146d7e0e35e7de9920d041f5a5621aabe"
            "02da3e2b09b405b77937efef3197bd5772e41fdb73fb5294478e45208063b5f58e"
            "089dbeb6d6342a909c1307b3fff5fe2cf4da56bdae50848f",
            156,
            "039c056d933b475032777edbaffac50f143f64c123329ed9cf59e3b65d3f43b6",
            178, 3, 4886999, 1 },
          { "8f3a06e2fd8711350a517bb12e31f3d3423e8dc0bb14aac8240fca0995938d59bb"
            "37bd0a7dfc9c9cc0705684b46612e8c8b1d6655fb0f9887562bb9899791a0250d1"
            "320f945eda48cdc20c233f40a5bb0a7e3ac5ad7250ce684f68fc0b8c9633bfd75a"
            "ad116525af7bdcdbbdb4e00ab163fd4df08f243f12557e",
            122,
            "90631f686a8c3dbc0703ffa353bc1fdf35774568ac62406f98a13ed8f47595fd",
            55, 1, 15738350, 1 },
          { "b540beb016a5366524d4605156493f9874514a5aa58818cd0c6dfffaa9e90205f1"
            "7b",
            34,
            "44071f6d181561670bda728d43fb79b443bb805afdebaf98622b5165e01b15fb",
            231, 1, 6631659, 1 },
          { "a14975c26c088755a8b715ff2528d647cd343987fcf4aa25e7194a8417fb2b4b3f"
            "7268da9f3182b4cfb22d138b2749d673a47ecc7525dd15a0a3c66046971784bb63"
            "d7eae24cc84f2631712075a10e10a96b0e0ee67c43e01c423cb9c44e5371017e9c"
            "496956b632158da3fe12addecb88912e6759bc37f9af2f45af72c5cae3b179ffb6"
            "76a697de6ebe45cd4c16d4a9d642d29ddc0186a0a48cb6cd62bfc3dd229d313b30"
            "1560971e740e2cf1f99a9a090a5b283f35475057e96d7064e2e0fc81984591068d"
            "55a3b4169f22cccb0745a2689407ea1901a0a766eb99",
            220,
            "3d968b2752b8838431165059319f3ff8910b7b8ecb54ea01d3f54769e9d98daf",
            167, 8, 10784179, 1 },
      };
    char          passwd[256];
    unsigned char salt[crypto_pwhash_argon2i_SALTBYTES];
    unsigned char out[256];
    char          out_hex[256 * 2 + 1];
    size_t        i = 0U;

    do {
        sodium_hex2bin((unsigned char *) passwd, sizeof passwd,
                       tests[i].passwd_hex, strlen(tests[i].passwd_hex), NULL,
                       NULL, NULL);
        sodium_hex2bin(salt, sizeof salt, tests[i].salt_hex,
                       strlen(tests[i].salt_hex), NULL, NULL, NULL);
        if (crypto_pwhash_argon2i(
                out, (unsigned long long) tests[i].outlen,
                passwd, tests[i].passwdlen,
                (const unsigned char *) salt, tests[i].opslimit,
                tests[i].memlimit) != 0) {
            printf("pwhash failure\n");
        }
        sodium_bin2hex(out_hex, sizeof out_hex, out, tests[i].outlen);
        printf("%s\n", out_hex);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}

static void tv2(void)
{
    static struct {
        const char         *passwd_hex;
        size_t              passwdlen;
        const char         *salt_hex;
        size_t              outlen;
        unsigned long long  opslimit;
        size_t              memlimit;
        unsigned int        lanes;
    } tests[] = {
          { "a347ae92bce9f80f6f595a4480fc9c2fe7e7d7148d371e9487d75f5c23008ffae0"
            "65577a928febd9b1973a5a95073acdbeb6a030cfc0d79caa2dc5cd011cef02c08d"
            "a232d76d52dfbca38ca8dcbd665b17d1665f7cf5fe59772ec909733b24de97d6f5"
            "8d220b20c60d7c07ec1fd93c52c31020300c6c1facd77937a597c7a6",
            127,
            "5541fbc995d5c197ba290346d2c559dedf405cf97e5f95482143202f9e74f5c2",
            155, 4, 1397645, 1 },
          { "a347ae92bce9f80f6f595a4480fc9c2fe7e7d7148d371e9487d75f5c23008ffae0"
            "65577a928febd9b1973a5a95073acdbeb6a030cfc0d79caa2dc5cd011cef02c08d"
            "a232d76d52dfbca38ca8dcbd665b17d1665f7cf5fe59772ec909733b24de97d6f5"
            "8d220b20c60d7c07ec1fd93c52c31020300c6c1facd77937a597c7a6",
            127,
            "5541fbc995d5c197ba290346d2c559dedf405cf97e5f95482143202f9e74f5c2",
            155, 3, 1397645, 1 },
      };
    char          passwd[256];
    unsigned char salt[crypto_pwhash_argon2i_SALTBYTES];
    unsigned char out[256];
    char          out_hex[256 * 2 + 1];
    size_t        i = 0U;

    do {
        sodium_hex2bin((unsigned char *)passwd, sizeof passwd,
                       tests[i].passwd_hex, strlen(tests[i].passwd_hex), NULL,
                       NULL, NULL);
        sodium_hex2bin(salt, sizeof salt, tests[i].salt_hex,
                       strlen(tests[i].salt_hex), NULL, NULL, NULL);
        if (crypto_pwhash_argon2i(
                out, (unsigned long long) tests[i].outlen,
                passwd, tests[i].passwdlen,
                (const unsigned char *) salt, tests[i].opslimit,
                tests[i].memlimit) != 0) {
            printf("pwhash failure\n");
        }
        sodium_bin2hex(out_hex, sizeof out_hex, out, tests[i].outlen);
        printf("%s\n", out_hex);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}

static void tv3(void)
{
    static struct {
        const char *passwd;
        const char *out;
    } tests[] = {
          { "^T5H$JYt39n%K*j:W]!1s?vg!:jGi]Ax?..l7[p0v:1jHTpla9;]bUN;?bWyCbtqg "
            "nrDFal+Jxl3,2`#^tFSu%v_+7iYse8-cCkNf!tD=KrW)",
            "$argon2i$m=22528,t=10,p=1$i2sXExTHR4py06Nh+P+Kwg$OvfhlngWzaXLI1LnHcQczduSg9u/pk6hhJwKhHEp/dk" },
          { "bl72h6#y<':MFRZ>B IA1=NRkCKS%W8`1I.2uQxJN0g)N N aTt^4K!Iw5r "
            "H6;crDsv^a55j9tsk'/GqweZn;cdk6+F_St6:#*=?ZCD_lw>.",
            "$argon2i$m=55296,t=3,p=1$vI46D/UykijxgIg6l928Rw$791WzR3L7stwlLZIv6eJr1CWHbR4L0e9tp6I4J5MZAc" },
          { "Py "
            ">e.5b+tLo@rL`dC2k@eJ&4eVl!W=JJ4+k&mAt@gt',FS1JjqKW3aq21:]^kna`"
            "mde7kVkN5NrpKUptu)@4*b&?BE_sJMG1=&@`3GBCV]Wg7xwgo7x3El",
            "$argon2i$m=32768,t=8,p=1$YsE+8BiiE2RqYp7QcuMJpw$TvmLKq03VJBFDXLtbUhOm+TyySgAXzi7dNT21SWRY7w" },
          { "2vj;Um]FKOL27oam(:Uo8+UmSTvb1FD*h?jk_,S=;RDgF-$Fjk?]9yvfxe@fN^!NN("
            "Cuml?+2Raa",
            "$argon2i$m=28672,t=4,p=1$Koen83S8tAM/TIPy/2+ndw$g5taoOiSre2HKbkodUH/1ap0wdwOwH5F0T23cCLfSwU" },
          { "CT=[9uUoGav,J`kU+348tA50ue#sL:ABZ3QgF+r[#vh:tTOiL>s8tv%,Jeo]jH/"
            "_4^i(*jD-_ku[9Ko[=86 06V",
            "$argon2i$m=26624,t=1,p=1$9/jJcwR3z6Y8ZMt4abl4vQ$zS2+Hiz0HzdOj4zdbffl5FgrM1lWN8bkatHrtod6BGg" },
          { "J#wNn`hDgOpTHNI.w^1a70%f,.9V_m038H_JIJQln`vdWnn/"
            "rmILR?9H5g(+`;@H(2VosN9Fgk[WEjaBr'yB9Q19-imNa04[Mk5kvGcSn-TV",
            "$argon2i$m=45056,t=4,p=1$bxd84vA1esVh3Q59k6rKMw$hMwksuneXVlZ2MN+ibfVIGomTDfBGF8k6BBG9Ick3mI" },
          { "j4BS38Asa;p)[K+9TY!3YDj<LK-`nLVXQw9%*QfM",
            "$argon2i$m=43008,t=6,p=1$azJ4t9a3eU7oT7oVHNWeSQ$8PuyUC/uXsnIFzkXiK7Wa/NGMqVzxQbE6MgPI101ANo" },
          { "M.R>Qw+!qJb]>pP :_.9`dxM9k [eR7Y!yL-3)sNs[R,j_/^ "
            "TH=5ny'15>6UXWcQW^6D%XCsO[vN[%ReA-`tV1vW(Nt*0KVK#]45P_A",
            "$argon2i$m=38912,t=5,p=1$FhNucCTljSINyYLzg2ATJg$09y/TogytLYVCBEDfT90O//ejbIuRyaCTcv1tcfwEhA" },
          { "K3S=KyH#)36_?]LxeR8QNKw6X=gFb'ai$C%29V* "
            "tyh^Wo$TN-#Q4qkmtTCf0LLb.^E$0uykkP",
            "$argon2i$m=23552,t=3,p=1$CIyn4RfRAlEctS1WNr/cWg$yAevM0sQq95wZsvA2LGnGqBNSNOCHmqC2uWTgNw+c5U" },
          { "Y0!?iQa9M%5ekffW(`",
            "$argon2i$m=33792,t=9,p=1$W0FAjH3H9bqV4ZNWkcryOA$uglFyolaH+qHrMMl4gpMvI3gtF9OJuQlZbinUpywvMc" }
      };
    char *out;
    char *passwd;
    size_t i = 0U;

    do {
        out = (char *) sodium_malloc(strlen(tests[i].out) + 1U);
        assert(out != NULL);
        memcpy(out, tests[i].out, strlen(tests[i].out) + 1U);
        passwd = (char *) sodium_malloc(strlen(tests[i].passwd) + 1U);
        assert(passwd != NULL);
        memcpy(passwd, tests[i].passwd, strlen(tests[i].passwd) + 1U);
        if (crypto_pwhash_argon2i_str_verify
            (out, passwd, strlen(passwd)) != 0) {
            printf("pwhash_str failure: [%u]\n", (unsigned int)i);
        }
        sodium_free(out);
        sodium_free(passwd);
    } while (++i < (sizeof tests) / (sizeof tests[0]));
}

int main(void)
{
    char       *str_out;
    char       *str_out2;
    char       *salt;
    const char *passwd = "Correct Horse Battery Staple";

    tv();
    tv2();
    tv3();
    salt = (char *) sodium_malloc(crypto_pwhash_argon2i_SALTBYTES);
    str_out = (char *) sodium_malloc(crypto_pwhash_argon2i_STRBYTES);
    str_out2 = (char *) sodium_malloc(crypto_pwhash_argon2i_STRBYTES);
    memcpy(salt, ">A 16-bytes salt",
           crypto_pwhash_argon2i_SALTBYTES);
    if (crypto_pwhash_argon2i_str(str_out, passwd, strlen(passwd),
                                  OPSLIMIT, MEMLIMIT) != 0) {
        printf("pwhash_str failure\n");
    }
    if (crypto_pwhash_argon2i_str(str_out2, passwd, strlen(passwd),
                                  OPSLIMIT, MEMLIMIT) != 0) {
        printf("pwhash_str(2) failure\n");
    }
    if (strcmp(str_out, str_out2) == 0) {
        printf("pwhash_str doesn't generate different salts\n");
    }
    if (crypto_pwhash_argon2i_str_verify(str_out, passwd,
                                         strlen(passwd)) != 0) {
        printf("pwhash_str_verify failure\n");
    }
    if (crypto_pwhash_argon2i_str_verify(str_out, passwd,
                                         strlen(passwd)) != 0) {
        printf("pwhash_str_verify failure\n");
    }
    str_out[14]++;
    if (crypto_pwhash_argon2i_str_verify(
            str_out, passwd, strlen(passwd)) == 0) {
        printf("pwhash_str_verify(2) failure\n");
    }
    str_out[14]--;

    assert(str_out[crypto_pwhash_argon2i_STRBYTES - 1U] == 0);
    assert(crypto_pwhash_argon2i_saltbytes() > 0U);
    assert(crypto_pwhash_argon2i_strbytes() > 1U);
    assert(crypto_pwhash_argon2i_strbytes() >
           strlen(crypto_pwhash_argon2i_strprefix()));
    assert(crypto_pwhash_argon2i_opslimit_interactive() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_interactive() > 0U);
    assert(crypto_pwhash_argon2i_opslimit_sensitive() > 0U);
    assert(crypto_pwhash_argon2i_memlimit_sensitive() > 0U);

    sodium_free(salt);
    sodium_free(str_out);
    sodium_free(str_out2);

    printf("OK\n");

    return 0;
}