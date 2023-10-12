#include "../kek.h"
#include <math.h>
#include <stdlib.h>

static const f64 wn[128] = {
	0x1.db4668fe7e4a4p-30, 0x1.16db47e193e1ap-33,
	0x1.73949184db9dfp-33, 0x1.b4c8fece48e83p-33,
	0x1.e8e576e43fbefp-33, 0x1.0a936da5e55adp-32,
	0x1.1e0ce6b5969b3p-32, 0x1.2f98d6bb4f41fp-32,
	0x1.3fabee1911cd7p-32, 0x1.4e94c08c0bab7p-32,
	0x1.5c8afdbf0217bp-32, 0x1.69b7b213f3f69p-32,
	0x1.763a1600eec74p-32, 0x1.822a858af0e7dp-32,
	0x1.8d9c6a9d35e3dp-32, 0x1.989f85c753b2cp-32,
	0x1.a340d1baf5b18p-32, 0x1.ad8b2506a137cp-32,
	0x1.b787a7c516f3bp-32, 0x1.c13e2b014e85cp-32,
	0x1.cab56ac6a38d3p-32, 0x1.d3f340dda611cp-32,
	0x1.dcfccc51c59f0p-32, 0x1.e5d6909f51b6ap-32,
	0x1.ee848e956826fp-32, 0x1.f70a5866c8f46p-32,
	0x1.ff6b21fffe31ap-32, 0x1.03d4e7391c5b7p-31,
	0x1.07e47d87a40f6p-31, 0x1.0be58456ff4aep-31,
	0x1.0fd911b97f236p-31, 0x1.13c024b2c7ec6p-31,
	0x1.179ba80463fecp-31, 0x1.1b6c7492c9735p-31,
	0x1.1f335374a10f8p-31, 0x1.22f0ffbaa1e55p-31,
	0x1.26a627fb9d120p-31, 0x1.2a536fae30e33p-31,
	0x1.2df97057e7efbp-31, 0x1.3198ba982d911p-31,
	0x1.3531d7146a43ep-31, 0x1.38c54749b9033p-31,
	0x1.3c538647ef792p-31, 0x1.3fdd09591d2a4p-31,
	0x1.436240982ad9dp-31, 0x1.46e39778de063p-31,
	0x1.4a617543306ccp-31, 0x1.4ddc3d83a5b84p-31,
	0x1.515450720f455p-31, 0x1.54ca0b4ffd349p-31,
	0x1.583dc8bff3219p-31, 0x1.5bafe11654817p-31,
	0x1.5f20aaa4dfc1ap-31, 0x1.62907a0176ebfp-31,
	0x1.65ffa248e016dp-31, 0x1.696e755e16b84p-31,
	0x1.6cdd4426b88a5p-31, 0x1.704c5ec50cb81p-31,
	0x1.73bc14d01a2c9p-31, 0x1.772cb58a39dd6p-31,
	0x1.7a9e90168b8eep-31, 0x1.7e11f3adaeb92p-31,
	0x1.81872fd21db73p-31, 0x1.84fe9484873b9p-31,
	0x1.88787278810a6p-31, 0x1.8bf51b49ef337p-31,
	0x1.8f74e1b37c6b8p-31, 0x1.92f819c682bf5p-31,
	0x1.967f1924c7b06p-31, 0x1.9a0a373c73f21p-31,
	0x1.9d99cd86b58b4p-31, 0x1.a12e37c983369p-31,
	0x1.a4c7d45d01a31p-31, 0x1.a867047516e4fp-31,
	0x1.ac0c2c6fc6382p-31, 0x1.afb7b428fe7a1p-31,
	0x1.b36a075498d64p-31, 0x1.b72395df5b73bp-31,
	0x1.bae4d457ee119p-31, 0x1.beae3c60cd0e4p-31,
	0x1.c2804d2c6b16fp-31, 0x1.c65b8c04dbac2p-31,
	0x1.ca4084e091e34p-31, 0x1.ce2fcb05f8c34p-31,
	0x1.d229f9bfeefdbp-31, 0x1.d62fb52580b86p-31,
	0x1.da41aaf79a344p-31, 0x1.de609397e09b9p-31,
	0x1.e28d331c6723cp-31, 0x1.e6c85a849b015p-31,
	0x1.eb12e91486bbcp-31, 0x1.ef6dcddc7d392p-31,
	0x1.f3da097460823p-31, 0x1.f858aff31cbf0p-31,
	0x1.fceaeb2ca5f17p-31, 0x1.00c8fea1720d4p-30,
	0x1.0327a1cc4cf5ep-30, 0x1.05921d1c4d769p-30,
	0x1.08093fe3e40e1p-30, 0x1.0a8ded0ec371ap-30,
	0x1.0d211dd28b00fp-30, 0x1.0fc3e4d95f278p-30,
	0x1.12777201834f3p-30, 0x1.153d16d45743dp-30,
	0x1.18164be0c1c39p-30, 0x1.1b04b731f6bccp-30,
	0x1.1e0a342cf08f6p-30, 0x1.2128dd36bdf09p-30,
	0x1.246317a6b53c0p-30, 0x1.27bba2b5dbc92p-30,
	0x1.2b35aa5ebee3ep-30, 0x1.2ed4df8099571p-30,
	0x1.329d9725e32f7p-30, 0x1.3694f3a3740d9p-30,
	0x1.3ac11b8e206d6p-30, 0x1.3f29848d3b416p-30,
	0x1.43d75b60bca1dp-30, 0x1.48d61806d6010p-30,
	0x1.4e3456b0e3a1bp-30, 0x1.54052012a04a4p-30,
	0x1.5a61edf7e8f32p-30, 0x1.616dff7c8f54ap-30,
	0x1.695c2be68edc9p-30, 0x1.7279dd4ac3f9dp-30,
	0x1.7d45eb36eb842p-30, 0x1.8aa73e440ffbcp-30,
	0x1.9c8e0c7c8098fp-30, 0x1.b8a7c476d2be8p-30
};

static const f64 fn[128] = {
	0x1.0000000000000p+0, 0x1.ed5cf060d53bbp-1,
	0x1.df6071934c096p-1, 0x1.d37a74ffb7e3fp-1,
	0x1.c8d923f9e066ep-1, 0x1.bf19b6810e602p-1,
	0x1.b6042cf903cb5p-1, 0x1.ad750b7255a18p-1,
	0x1.a55418110d29fp-1, 0x1.9d8fdfaec7beap-1,
	0x1.961b4c1afe57ap-1, 0x1.8eec3c5bbfb34p-1,
	0x1.87faa61a739e6p-1, 0x1.814005219cc6ep-1,
	0x1.7ab6f9c656c14p-1, 0x1.745b04d027f1cp-1,
	0x1.6e2856a006c14p-1, 0x1.681bab4ebdc18p-1,
	0x1.62322fc593a59p-1, 0x1.5c696d348e881p-1,
	0x1.56bf39249a236p-1, 0x1.5131a8efe6179p-1,
	0x1.4bbf07c6c217dp-1, 0x1.4665cea500fb2p-1,
	0x1.41249dc646445p-1, 0x1.3bfa374538788p-1,
	0x1.36e57aa698262p-1, 0x1.31e5612065cfcp-1,
	0x1.2cf8fa78591b5p-1, 0x1.281f6a5d2446ap-1,
	0x1.2357e62428f89p-1, 0x1.1ea1b2d9efcb5p-1,
	0x1.19fc239747fabp-1, 0x1.1566980fb8bacp-1,
	0x1.10e07b5015e52p-1, 0x1.0c6942a5bbca5p-1,
	0x1.08006ca84dde0p-1, 0x1.03a58060e667cp-1,
	0x1.feb0191503b06p-2, 0x1.f62f4dd04549dp-2,
	0x1.edc7d75b77106p-2, 0x1.e578f9f2c936cp-2,
	0x1.dd4204b58297ep-2, 0x1.d52250cd9b948p-2,
	0x1.cd1940ad1b140p-2, 0x1.c5263f5e989c0p-2,
	0x1.bd48bfe6a41dfp-2, 0x1.b5803cb422f1dp-2,
	0x1.adcc371df4166p-2, 0x1.a62c36ec664dap-2,
	0x1.9e9fc9ed3ad0ap-2, 0x1.97268391186b6p-2,
	0x1.8fbffc917614cp-2, 0x1.886bd29e22628p-2,
	0x1.8129a811a7651p-2, 0x1.79f923abe1175p-2,
	0x1.72d9f05230366p-2, 0x1.6bcbbcd4c4723p-2,
	0x1.64ce3bb887d89p-2, 0x1.5de12305426e6p-2,
	0x1.57042c17986d6p-2, 0x1.503713768fb3fp-2,
	0x1.497998ac51ea1p-2, 0x1.42cb7e21e8c52p-2,
	0x1.3c2c88fdb8dd0p-2, 0x1.359c810485cb7p-2,
	0x1.2f1b307ccfe9ap-2, 0x1.28a864146107ep-2,
	0x1.2243eac7e2068p-2, 0x1.1bed95cc5751fp-2,
	0x1.15a5387a66034p-2, 0x1.0f6aa83b46cf7p-2,
	0x1.093dbc774f1a0p-2, 0x1.031e4e85fb6a1p-2,
	0x1.fa18733ed2789p-3, 0x1.ee0eb59e61862p-3,
	0x1.e21f21d12332ep-3, 0x1.d64978f7cf9d6p-3,
	0x1.ca8d7f9ac2021p-3, 0x1.beeafd99d710fp-3,
	0x1.b361be1eb801cp-3, 0x1.a7f18f918fb5cp-3,
	0x1.9c9a43902c0f3p-3, 0x1.915baee792bf0p-3,
	0x1.8635a99016373p-3, 0x1.7b280eabfd4b9p-3,
	0x1.7032bc88d676ap-3, 0x1.655594a396d54p-3,
	0x1.5a907baface5fp-3, 0x1.4fe359a138234p-3,
	0x1.454e19baa0e72p-3, 0x1.3ad0aa9dd7fa4p-3,
	0x1.306afe6193144p-3, 0x1.261d0aaaebe72p-3,
	0x1.1be6c8cbda96fp-3, 0x1.11c835e71b728p-3,
	0x1.07c1531a2b49bp-3, 0x1.fba44b5c4de8bp-4,
	0x1.e7f56ea105fbcp-4, 0x1.d4762ca983a5ap-4,
	0x1.c126ac011775fp-4, 0x1.ae071dc7af28fp-4,
	0x1.9b17be7e63eebp-4, 0x1.8858d6f54ff30p-4,
	0x1.75cabd60e5dbbp-4, 0x1.636dd69e8c211p-4,
	0x1.514297b239a5bp-4, 0x1.3f4987896ad6ap-4,
	0x1.2d8341133a33bp-4, 0x1.1bf075c20a9fep-4,
	0x1.0a91f09183c33p-4, 0x1.f2d13368bd127p-5,
	0x1.d0eaf63395868p-5, 0x1.af738c17a5016p-5,
	0x1.8e6db483bc1bbp-5, 0x1.6ddc9dd1fe248p-5,
	0x1.4dc3fcbd99702p-5, 0x1.2e282b724adacp-5,
	0x1.0f0e539c89b76p-5, 0x1.e0f951d57e236p-6,
	0x1.a4f57a25d9cbdp-6, 0x1.6a23fa9d5f276p-6,
	0x1.309cee4e09981p-6, 0x1.f100847645165p-7,
	0x1.83f4bed19339ap-7, 0x1.1a9b6b3fc1937p-7,
	0x1.6ba8b0ffb627ep-8, 0x1.5de9e33726f20p-9
};

static const unsigned int kn[128] = {
	0x76ad2212, 0x0,        0x600f1b53, 0x6ce447a6,
	0x725b46a2, 0x7560051d, 0x774921eb, 0x789a25bd,
	0x799045c3, 0x7a4bce5d, 0x7adf629f, 0x7b5682a6,
	0x7bb8a8c6, 0x7c0ae722, 0x7c50cce7, 0x7c8cec5b,
	0x7cc12cd6, 0x7ceefed2, 0x7d177e0b, 0x7d3b8883,
	0x7d5bce6c, 0x7d78dd64, 0x7d932886, 0x7dab0e57,
	0x7dc0dd30, 0x7dd4d688, 0x7de73185, 0x7df81cea,
	0x7e07c0a3, 0x7e163efa, 0x7e23b587, 0x7e303dfd,
	0x7e3beec2, 0x7e46db77, 0x7e51155d, 0x7e5aabb3,
	0x7e63abf7, 0x7e6c222c, 0x7e741906, 0x7e7b9a18,
	0x7e82adfa, 0x7e895c63, 0x7e8fac4b, 0x7e95a3fb,
	0x7e9b4924, 0x7ea0a0ef, 0x7ea5b00d, 0x7eaa7ac3,
	0x7eaf04f3, 0x7eb3522a, 0x7eb765a5, 0x7ebb4259,
	0x7ebeeafd, 0x7ec2620a, 0x7ec5a9c4, 0x7ec8c441,
	0x7ecbb365, 0x7ece78ed, 0x7ed11671, 0x7ed38d62,
	0x7ed5df12, 0x7ed80cb4, 0x7eda175c, 0x7edc0005,
	0x7eddc78e, 0x7edf6ebf, 0x7ee0f647, 0x7ee25ebe,
	0x7ee3a8a9, 0x7ee4d473, 0x7ee5e276, 0x7ee6d2f5,
	0x7ee7a620, 0x7ee85c10, 0x7ee8f4cd, 0x7ee97047,
	0x7ee9ce59, 0x7eea0eca, 0x7eea3147, 0x7eea3568,
	0x7eea1aab, 0x7ee9e071, 0x7ee98602, 0x7ee90a88,
	0x7ee86d08, 0x7ee7ac6a, 0x7ee6c769, 0x7ee5bc9c,
	0x7ee48a67, 0x7ee32efc, 0x7ee1a857, 0x7edff42f,
	0x7ede0ffa, 0x7edbf8d9, 0x7ed9ab94, 0x7ed7248d,
	0x7ed45fae, 0x7ed1585c, 0x7ece095f, 0x7eca6ccb,
	0x7ec67be2, 0x7ec22eee, 0x7ebd7d1a, 0x7eb85c35,
	0x7eb2c075, 0x7eac9c20, 0x7ea5df27, 0x7e9e769f,
	0x7e964c16, 0x7e8d44ba, 0x7e834033, 0x7e781728,
	0x7e6b9933, 0x7e5d8a1a, 0x7e4d9ded, 0x7e3b737a,
	0x7e268c2f, 0x7e0e3ff5, 0x7df1aa5d, 0x7dcf8c72,
	0x7da61a1e, 0x7d72a0fb, 0x7d30e097, 0x7cd9b4ab,
	0x7c600f1a, 0x7ba90bdc, 0x7a722176, 0x77d664e5,
};

f64 u01(void);
u64 xoshiro256starstar(void);
vec rnorm2(u64 n, f64 mean, f64 sd) {
	rinit(0);
	f64 *x = malloc(n * sizeof x[0]);
	for (u64 i = 0; i < n; i++) {
		int hz = xoshiro256starstar();
		u64 iz = hz & 127;
		if (llabs(hz) < kn[iz]) {
			x[i] = mean + sd * hz * wn[iz];
		} else {
			f64 r = 3.4426198558966521214;
			f64 x1, y;
			f64 tmp;
			while (1) {
				x1 = hz * wn[iz];
				if (iz == 0) {
					do {
						x1 = -log(u01()) / r;
						y = -log(u01());
					} while (y + y < x1 * x1);
					if (hz > 0) {
						tmp = r + x1;
						break;
					} else {
						tmp = -(r + x1);
						break;
					}
				}
				if (fn[iz] + u01() * (fn[iz - 1] - fn[iz]) < exp(-0.5 * x1 * x1)) {
					tmp = x1;
					break;
				}
				hz = xoshiro256starstar();
				iz = hz & 127;
				if ((u64) labs(hz) < kn[iz]) {
					tmp = hz * wn[iz];
					break;
				}
			}
			x[i] = mean + sd * tmp;
		}
	}
	return (vec) {n, x};
}
