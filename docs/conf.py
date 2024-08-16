
# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from fnmatch import fnmatch
from os import environ, path, sep, walk
from subprocess import check_call, check_output
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
    'sphinx.ext.graphviz',
    'sphinx.ext.inheritance_diagram',
    'sphinx.ext.intersphinx',
    'sphinx.ext.mathjax',
    'sphinx.ext.todo',
    'sphinx_favicon',
    'notfound.extension',
    # 'breathe',
    'javasphinx',
    'sphinx_csharp.csharp',
    'sphinxcontrib.makedomain',
    'sphinx_tags',
#    "sphinx_rust",
]
rust_crates = [
    "../rust",
]
html_css_files = [
    'style.css',
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

tags_create_tags = True

language = 'english'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

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
    ('c', 'c'),
    # ('cb', 'cobol'),
    # ('cl', 'clojure'),
    ('cp', 'cplusplus'),
    ('cs', 'csharp'),
    # ('d', 'd'),
    # ('da', 'dart'),
    # ('el', 'elixir'),
    # ('ev', 'eiffel'),
    # ('fr', 'fortran'),
    # ('fs', 'fsharp'),
    # ('go', 'go'),
    # ('hs', 'haskell'),
    ('ja', 'java'),
    ('js', 'javascript'),
    # ('ju', 'julia'),
    # ('kt', 'kotlin'),
    # ('ls', 'lisp'),
    # ('lu', 'lua'),
    # ('ma', 'matlab'),
    # ('oc', 'ocaml'),
    # ('pe', 'perl'),
    # ('ph', 'php'),
    # ('pr', 'prolog'),
    ('py', 'python'),
    # ('r', 'r'),
    # ('rb', 'ruby'),
    ('rs', 'rust'),
    # ('sa', 'scala'),
    # ('se', 'scheme'),
    # ('sh', 'bash'),
    # ('sm', 'smalltalk'),
    # ('sq', 'sql'),
    # ('sw', 'swift'),
    # ('ts', 'typescript'),
    # ('vb', 'visualbasic'),
]
extlinks = {
    'prob': ('https://projecteuler.net/problem=%s',
             'Problem #%s'),
    'source': ('https://github.com/LivInTheLookingGlass/Euler/blob/main/%s',
               'here on GitHub!%.0s'),
    'live-test': ('/_static/test-%s.html',
                  'click here!%.0s'),
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

intersphinx_mapping = {
    'python':           ('https://docs.python.org/3', None),
    'matplotlib':       ('https://matplotlib.org/stable/', None),
    'Sphinx':           ('https://www.sphinx-doc.org/en/stable/', None),
    'sortedcontainers': ('https://grantjenks.com/docs/sortedcontainers/', None),
    'u-msgpack-python': ('https://u-msgpack-python.readthedocs.io/en/latest/', None),
    'pytest':           ('https://docs.pytest.org/en/stable/', None),
    'coverage':         ('https://coverage.readthedocs.io/en/latest/', None)
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


def countfiles(lang):
    templates = {
        'Makefile': lambda root, filename: filename == 'Makefile',
        'Python': lambda root, filename: fnmatch(filename, '*.py') and 'docs' not in root,
        'C': lambda root, filename: fnmatch(filename, '*.c') or fnmatch(filename, '*.h'),
        'C++': lambda root, filename: fnmatch(filename, '*.cpp') or fnmatch(filename, '*.h'),
        'C#': lambda root, filename: fnmatch(filename, '*.cs'),
        'Java': lambda root, filename: fnmatch(filename, '*.java'),
        'JavaScript': lambda root, filename: fnmatch(filename, '*.js'),
        'Rust': lambda root, filename: fnmatch(filename, '*.rs'),
    }
    exclude_patterns = {
        'Makefile': ['Unity', 'wasi-libc', 'node_modules'],
        'Python': ['Unity', 'docs'],
        'C': ['c/Unity', 'c/wasi-libc', 'cplusplus'],
        'C++': ['c/', 'cplusplus/Unity'],
        'C#': [],
        'Java': [],
        'JavaScript': ['node_modules', 'dist', 'target'],
        'Rust': ['Unity'],
    }
    count = 0

    for root, dirs, files in walk(basedir):
        if any(excluded in root for excluded in exclude_patterns.get(lang, [])):
            continue
        for filename in files:
            if templates[lang](root, filename):
                count += 1
    return count


def setup(app):
    try:
        langs = linguist(basedir)
        labels = [lang[0] for lang in langs]
        counts = [countfiles(lang) for lang in labels]
        sizes = [lang[1] for lang in langs]
        color_map = {
            'C': "#555555",
            'C++': "#f34b7d",
            'C#': "#178600",
            'Java': "#b07219",
            'JavaScript': "#f1e05a",
            'Python': "#3572A5",
            'Rust': "#dea584",
            'Makefile': "#427819",
        }
        colors = [color_map[lang] for lang in labels]
        _, ax = plt.subplots()
        ax.pie(sizes, labels=labels, colors=colors, autopct='%1.1f%%', labeldistance=None, pctdistance=0.85)
        plt.legend(title='Languages', loc='right', bbox_to_anchor=(1,0.5), bbox_transform=plt.gcf().transFigure)
        plt.savefig('languages.svg', transparent=True, bbox_inches='tight')

        sizes = [float(size) / count for size, count in zip(sizes, counts)]
        pairs = sorted(zip(sizes, labels), reverse=True)
        labels = [lang[1] for lang in pairs]
        sizes = [lang[0] for lang in pairs]
        pos = labels.index('Makefile')
        labels.pop(pos)
        sizes.pop(pos)
        colors = [color_map[lang] for lang in labels]
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
            'fn': {
            },
            'enum': {
            },
            'struct': {
            },
            'var': {
            },
            'crate': {
            }
        }
    ))

    # app.add_domain(custom_domain(
    #     'JavaDomain',
    #     'java',
    #     'Java',
    #     {
    #         'class': {
    #         },
    #         'method': {
    #         },
    #     }
    # ))

