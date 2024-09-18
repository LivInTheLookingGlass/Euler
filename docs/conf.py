from fnmatch import fnmatch
from os import environ, path, sep, walk
from pathlib import Path
from zlib import compress
from subprocess import check_call
from sys import path as sys_path

from sphinxcontrib.domaintools import custom_domain
try:
    from ghlinguist import linguist
    import matplotlib.pyplot as plt
except Exception:
    pass

basedir = path.abspath(path.join(path.dirname(__file__), '..'))
sys_path.insert(0, basedir)
sys_path.insert(0, basedir + sep + 'python')

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

project = 'Euler'
copyright = '2024, Olivia Appleton'
author = 'Olivia Appleton'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.duration',
    'sphinx.ext.extlinks',
    'sphinx.ext.githubpages',
    # 'sphinx.ext.graphviz',
    # 'sphinx.ext.inheritance_diagram',
    'sphinx.ext.intersphinx',
    'sphinx-mathjax-offline',
    # 'sphinx.ext.todo',
    'sphinx_favicon',
    'notfound.extension',
    # 'breathe',
    'javasphinx',
    'sphinx_csharp.csharp',
    'sphinxcontrib.makedomain',
    'sphinx_tags',
    # 'sphinx-disqus',
    # 'sphinx-computron',
    # 'sphinx-compendia',
    # 'sphinx-navtree',
    'sphinxcontrib.luadomain',
    'sphinxfortran.fortran_domain',
]

try:
    check_call(['rpm-ostree', '--version'])
    IS_SILVERBLUE = True
except Exception:
    IS_SILVERBLUE = False

if 'TERMUX_VERSION' not in environ and not IS_SILVERBLUE:
    extensions.append('sphinx_js')

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

language = 'english'
trim_footnote_reference_space = True

# -- Options for Python domain -----------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-the-python-domain

add_module_name = False
python_display_short_literal_types = True

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_css_files = [
    'https://cdn.datatables.net/1.10.23/css/jquery.dataTables.min.css',
    'style.css'
]
html_js_files = [
    'https://cdn.datatables.net/1.10.23/js/jquery.dataTables.min.js',
    'main.js',
]

# -- Options for autodoc extension -------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html#configuration

autodoc_member_order = 'bysource'

# -- Options for autosection extension ---------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/autosection.html#configuration

autosectionlabel_prefix_document = True

# -- Options for extlinks extension ------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/extlinks.html#configuration

langcodes = [
    # ('a', 'ada'),
    # ('ba', 'batch'),
    ('c', 'c'),                 # built-in
    # ('cb', 'cobol'),
    # ('cl', 'clojure'),
    ('cp', 'cplusplus'),        # built-in
    ('cs', 'csharp'),           # sphinx_csharp.csharp
    # ('d', 'd'),
    # ('da', 'dart'),           # sphinxcontrib-dartdomain
    # ('el', 'elixir'),
    # ('ev', 'eiffel'),
    ('fr', 'fortran'),          # sphinx-fortran
    # ('fs', 'fsharp'),
    # ('go', 'go'),             # sphinxcontrib-golangdomain
    # ('hs', 'haskell'),
    ('ja', 'java'),             # javasphinx
    ('js', 'javascript'),       # sphinx_js
    # ('ju', 'julia'),
    # ('kt', 'kotlin'),
    # ('ls', 'lisp'),           # sphinxcontrib-cldomain
    ('lu', 'lua'),              # sphinx-lua or sphinxcontrib-luadomain
    # ('ma', 'matlab'),         # sphinxcontrib-matlabdomain
    # ('mk', 'makefile'),       # hacked together with sphinxcontrib-domaintools
    # ('oc', 'ocaml'),          # sphinxcontrib-ocaml
    # ('pe', 'perl'),
    # ('ph', 'php'),            # sphinxcontrib-phpdomain
    # ('pr', 'prolog'),         # sphinx-prolog
    ('py', 'python'),           # built-in
    # ('r', 'r'),
    # ('rb', 'ruby'),
    ('rs', 'rust'),             # hacked together with sphinxcontrib-domaintools, but sphinxcontrib-rust might work
    # ('sa', 'scala'),          # sphinxcontrib-scaladomain
    # ('se', 'scheme'),
    # ('sh', 'bash'),
    # ('sm', 'smalltalk'),
    # ('sq', 'sql'),
    # ('sw', 'swift'),
    # ('ts', 'typescript'),     # sphinx_js
    # ('vb', 'visualbasic'),
]
extlinks = {
    'prob': ('https://projecteuler.net/problem=%s', '\u200BProblem #%s'),
    'source': ('https://github.com/LivInTheLookingGlass/Euler/blob/main/%s', 'here on GitHub!%.0s'),
    'live-test': ('/_static/test-%s.html', 'click here!%.0s'),
    'csref': ('https://learn.microsoft.com/en-us/dotnet/api/%s', '%s'),
} | {
    f'{code}-d': (f'./src/{lang}/p%s.html', '✔%.0s') for (code, lang) in langcodes
} | {
    f'{code}-s': (f'./src/{lang}/p%s.html', '⏱%.0s') for (code, lang) in langcodes
} | {
    f'{code}-i': (f'./src/{lang}/p%s.html', '🛠%.0s') for (code, lang) in langcodes
}
extlinks_detect_hardcoded_links = True

# -- Options for intersphinx extension ---------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/intersphinx.html#configuration

with Path(__file__).parent.joinpath('raw_inv.txt').open('rb') as f, Path(__file__).parent.joinpath('objects.inv').open('wb') as g:
    g.writelines(f.readline() for _ in range(4))
    g.write(compress(f.read()))

intersphinx_mapping = {
    'python':           ('https://docs.python.org/3', None),
    'matplotlib':       ('https://matplotlib.org/stable/', None),
    'Sphinx':           ('https://www.sphinx-doc.org/en/stable/', None),
    'sortedcontainers': ('https://grantjenks.com/docs/sortedcontainers/', None),
    'u-msgpack-python': ('https://u-msgpack-python.readthedocs.io/en/latest/', None),
    'pytest':           ('https://docs.pytest.org/en/stable/', None),
    'coverage':         ('https://coverage.readthedocs.io/en/latest/', None),
    'misc':             ('', './objects.inv'),
}

# -- Options for todo extension ----------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/extensions/todo.html#configuration

todo_include_todos = True

# -- Options for favicon extension -------------------------------------------
# https://sphinx-favicon.readthedocs.io/en/latest/configuration.html

favicons = [
    {
        "rel": "apple-touch-icon",
        "href": "https://projecteuler.net/favicons/apple-touch-icon.png",
    },
    {"href": "https://projecteuler.net/favicons/favicon-32x32.png"},
    {"href": "https://projecteuler.net/favicons/favicon-16x16.png"},
    {"href": "https://projecteuler.net/favicons/favicon.ico"},
]

# -- Options for sphinx-js extension -----------------------------------------
# https://github.com/mozilla/sphinx-js

root_for_relative_js_paths = basedir + sep + 'javascript'
js_source_path = [
    root_for_relative_js_paths + sep + 'src',
    root_for_relative_js_paths + sep + 'src' + sep + 'lib'
]

# -- Options for sphinx-tags extension ---------------------------------------
# https://sphinx-tags.readthedocs.io/en/latest/configuration.html

tags_create_tags = True
tags_page_title = 'Tags'

# Language chart generation + custom domains

def countfiles(lang):
    templates = {
        'C': lambda _, filename: fnmatch(filename, '*.c') or fnmatch(filename, '*.h'),
        'C++': lambda _, filename: fnmatch(filename, '*.cpp') or fnmatch(filename, '*.h') or fnmatch(filename, '*.hpp'),
        'C#': lambda _, filename: fnmatch(filename, '*.cs'),
        'Fortran': lambda _, filename: fnmatch(filename, '*.for'),
        'Java': lambda _, filename: fnmatch(filename, '*.java'),
        'JavaScript': lambda _, filename: fnmatch(filename, '*.js'),
        'Lua': lambda _, filename: fnmatch(filename, '*.lua'),
        'Makefile': lambda _, filename: filename == 'Makefile',
        'Python': lambda root, filename: fnmatch(filename, '*.py'),
        'Rust': lambda _, filename: fnmatch(filename, '*.rs'),
    }
    exclude_patterns = {
        'Makefile': ['Unity', 'wasi-libc', 'node_modules'],
        'Python': ['Unity', 'docs'],
        'C': ['c/Unity', 'cplusplus'],
        'C++': ['c/', 'cplusplus/Unity'],
        'JavaScript': ['node_modules', 'dist', 'target', 'docs', 'fallbacks'],
        'Rust': ['Unity'],
    }
    count = 0

    for root, _, files in walk(basedir):
        if any(excluded in root for excluded in exclude_patterns.get(lang, [])):
            continue
        for filename in files:
            if templates[lang](root, filename):
                count += 1
    return count


def setup(app):
    try:
        labels, sizes, counts = zip(*((lang, float(size), countfiles(lang)) for lang, size in linguist(basedir)))
        size = max(10, len(labels))
        colormap = plt.get_cmap('tab10' if len(labels) <= 10 else 'tab20')
        colors = [colormap(idx / size) for idx, _ in enumerate(labels)]
        _, ax = plt.subplots()
        ax.pie(sizes, labels=labels, colors=colors, autopct='%1.1f%%', labeldistance=None, pctdistance=0.85)
        plt.legend(title='Languages', loc='right', bbox_to_anchor=(1,0.5), bbox_transform=plt.gcf().transFigure)
        plt.savefig('languages.svg', transparent=True, bbox_inches='tight')

        sizes = [size / count for size, count in zip(sizes, counts)]
        sizes, labels, colors = zip(
            *sorted(filter(lambda x: x[1] != "Makefile", zip(sizes, labels, colors)), reverse=True)
        )
        _, ax = plt.subplots()
        ax.pie(sizes, labels=labels, colors=colors, autopct='%1.1f%%', labeldistance=None, pctdistance=0.85)
        plt.legend(title='Languages', loc='right', bbox_to_anchor=(1,0.5), bbox_transform=plt.gcf().transFigure)
        plt.savefig('languages-normalized.svg', transparent=True, bbox_inches='tight')
    except Exception:
        if 'GITHUB_ACTION' in environ:
            raise

    app.add_domain(custom_domain(
        'RustDomain',
        'rust',
        'Rust',
        {
            'fn': {},
            'enum': {},
            'struct': {},
            'trait': {},
            'macro': {},
        }
    ))
