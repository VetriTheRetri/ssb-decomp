use indoc::printdoc;
use std::{ffi::OsStr, path::PathBuf};

mod link;
mod pack;
mod unpack;

type ArgResult<T> = Result<T, pico_args::Error>;

fn print_usage() {
    printdoc!(
        r#"
        {name} {version}
        A utility to pack and unpack the image banks in SSB64

        Usage:
          -h, --help      print this help message
          -V, --version   print version info
          unpack          extract images and info from N64 image bank binary
          pack-entry      generate a `gas` assmebly file from `unpack`ed config
          link            generate a GNU `ld` script to combine entries

        {name} unpack <bank>:
          <bank>                      path to image bank data
          -o, --output <directory>    output directory for unpacked image files
          [-e, --extra]               indicate a misformed bank with an contains
                                      an extra bank entry at the end of the bank
        
        {name} pack-entry <config>:
          <config>                    path to entry config file generated by `unpack`
          [-o, --output <file>]       output file (default is based on `config`)
          [-i, --imgext <ext>]        extension for image bins (default: .{{format}}{{depth}})
          [-p, --palext <ext>]        extension for palette bins (default: .pal.bin)

        {name} link <config>:
          <config>                    path to bank config file generated by `unpack`
          [-s, --section <name>]      section name for linking (default: .rodata)
          [-o, --output <file>]       output path (default: <config>>.ld)

        "#,
        name = env!("CARGO_BIN_NAME"),
        version = env!("CARGO_PKG_VERSION")
    );
}

fn print_version() {
    println!(
        "{} version {}",
        env!("CARGO_BIN_NAME"),
        env!("CARGO_PKG_VERSION")
    );
}

fn main() {
    if let Err(e) = run() {
        eprintln!("{:?}", e);
        std::process::exit(1);
    }
}

fn run() -> anyhow::Result<()> {
    let args = Args::from_env()?;

    match args {
        Args::Unpack {
            bank,
            output,
            extra,
        } => unpack::unpack_bank(bank, output, extra),
        Args::PackEntry {
            config,
            output,
            imgext,
            palext,
        } => pack::pack_entry(config, output, imgext, palext),
        Args::Link {
            config,
            output,
            section,
        } => link::generate_script(config, output, section),
        Args::Help => Ok(print_usage()),
        Args::Version => Ok(print_version()),
    }
}

enum Args {
    Unpack {
        bank: PathBuf,
        output: PathBuf,
        extra: bool,
    },
    PackEntry {
        config: PathBuf,
        output: Option<PathBuf>,
        imgext: Option<String>,
        palext: Option<String>,
    },
    Link {
        config: PathBuf,
        section: Option<String>,
        output: Option<PathBuf>,
    },
    Help,
    Version,
}

impl Args {
    fn from_env() -> ArgResult<Self> {
        let mut args = pico_args::Arguments::from_env();

        if args.contains(["-h", "--help"]) {
            return Ok(Self::Help);
        }

        if args.contains(["-V", "--version"]) {
            return Ok(Self::Version);
        }

        match args.subcommand()?.as_deref() {
            Some("unpack") => {
                let output = args.value_from_os_str(["-o", "--output"], to_pathbuf)?;
                let extra = args.contains(["-e", "--extra"]);
                let bank = args.free_from_os_str(to_pathbuf)?;

                Ok(Self::Unpack {
                    bank,
                    output,
                    extra,
                })
            }
            Some("pack-entry") => {
                let output = args.opt_value_from_os_str(["-o", "--output"], to_pathbuf)?;
                let imgext = args.opt_value_from_str(["-i", "--imgext"])?;
                let palext = args.opt_value_from_str(["-p", "--palext"])?;
                let config = args.free_from_os_str(to_pathbuf)?;

                Ok(Self::PackEntry {
                    config,
                    output,
                    imgext,
                    palext,
                })
            }
            Some("link") => {
                let section = args.opt_value_from_str(["-s", "--section"])?;
                let output = args.opt_value_from_os_str(["-o", "--output"], to_pathbuf)?;
                let config = args.free_from_os_str(to_pathbuf)?;

                Ok(Self::Link {
                    config,
                    section,
                    output,
                })
            }
            Some(unk) => {
                println!("Unrecognized subcommand \"{}\"", unk);
                Ok(Self::Help)
            }
            None => Ok(Self::Help),
        }
    }
}

fn to_pathbuf(s: &OsStr) -> ArgResult<PathBuf> {
    Ok(PathBuf::from(s.to_os_string()))
}
