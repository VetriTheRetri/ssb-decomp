use failure::Error;
use std::path::PathBuf;
use structopt::StructOpt;

#[macro_use]
mod format;
mod link;
mod pack;
mod unpack;

/// A utility to pack and unpack the image banks in SSB64.
#[derive(Debug, StructOpt)]
enum Opts {
    /// Extract images and information from the native N64 big-endian image bank format
    #[structopt(name = "unpack")]
    Unpack {
        /// image bank to extract
        #[structopt(parse(from_os_str))]
        bank: PathBuf,
        /// Output directory for unpacked image files
        #[structopt(short, long, parse(from_os_str))]
        output: PathBuf,
        /// indicate a misformed bank that (erroneously?) has the end of bank entry
        #[structopt(short, long)]
        extra: bool,
    },
    /// Generate a GNU as assembly file that recreates the original entry    
    #[structopt(name = "pack-entry")]
    PackEntry {
        /// config file generated by 'unpack'
        #[structopt(parse(from_os_str))]
        config: PathBuf,
        /// specify output file (otherwise based on config name)
        #[structopt(short, long, parse(from_os_str))]
        output: Option<PathBuf>,
        /// specifiy a specific extension for image binaries
        /// by default, uses "base.{format}{depth}"
        #[structopt(short, long)]
        imgext: Option<String>,
        /// specifiy a specific extension for palette binaries
        /// by default, uses "base.pal.bin"
        #[structopt(short, long)]
        palext: Option<String>,
    },
    /// Generate a GNU ld Linker Script for combining various entry objects
    #[structopt(name = "link")]
    Link {
        /// config file generated by 'unpack'
        #[structopt(parse(from_os_str))]
        config: PathBuf,
        /// use a custom section for the location of entry data (default: .rodata)
        #[structopt(short, long)]
        section: Option<String>,
        /// use a custom output (default: config-name.ld)
        #[structopt(short, long, parse(from_os_str))]
        output: Option<PathBuf>,
    },
}

fn main() {
    let opts = Opts::from_args();
    if let Err(e) = run(opts) {
        eprintln!("Error: {}", e);
        for c in e.iter_causes() {
            eprintln!("caused by: {}", c);
        }

        ::std::process::exit(1);
    }
}

fn run(opts: Opts) -> Result<(), Error> {
    match opts {
        Opts::Unpack {
            bank,
            output,
            extra,
        } => unpack::unpack_bank(bank, output, extra),
        Opts::PackEntry {
            config,
            output,
            imgext,
            palext,
        } => pack::pack_entry(config, output, imgext, palext),
        Opts::Link {
            config,
            output,
            section,
        } => link::generate_script(config, output, section),
    }
}
